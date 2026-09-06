#include <stdint.h>

extern void lexer_string_lit_overflow_reset(void);
extern int32_t lexer_string_lit_overflow_pending(void);
extern void lexer_note_string_lit_overflow(int32_t line, int32_t col);
extern void lexer_ident_too_long_reset(void);
extern int32_t lexer_ident_too_long_pending(void);
extern int32_t ast_pipeline_onefunc_append_const(uint8_t * restrict out, uint8_t * restrict name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t ast_pipeline_onefunc_const_init_ref(uint8_t * restrict out, int32_t i);
extern int32_t ast_pipeline_onefunc_const_type_ref(uint8_t * restrict out, int32_t i);
/* C-04 -E-extern TU aliases */
/* C-04 parser: ast_expr_init_match_enum after struct ast_Expr */
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
#define std_io_core_xlang_io_unregister_provided_buffers xlang_io_unregister_provided_buffers
#define std_io_core_xlang_io_provided_buffer_ptr xlang_io_provided_buffer_ptr
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
extern void xlang_io_unregister_provided_buffers(void);
extern uint8_t *xlang_io_provided_buffer_ptr(uint32_t bid);
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
enum token_TokenKind { token_TokenKind_TOKEN_EOF, token_TokenKind_TOKEN_FUNCTION, token_TokenKind_TOKEN_LET, token_TokenKind_TOKEN_CONST, token_TokenKind_TOKEN_IF, token_TokenKind_TOKEN_ELSE, token_TokenKind_TOKEN_WHILE, token_TokenKind_TOKEN_LOOP, token_TokenKind_TOKEN_FOR, token_TokenKind_TOKEN_BREAK, token_TokenKind_TOKEN_CONTINUE, token_TokenKind_TOKEN_RETURN, token_TokenKind_TOKEN_PANIC, token_TokenKind_TOKEN_DEFER, token_TokenKind_TOKEN_TRY, token_TokenKind_TOKEN_CATCH, token_TokenKind_TOKEN_REGION, token_TokenKind_TOKEN_WITH_ARENA, token_TokenKind_TOKEN_MATCH, token_TokenKind_TOKEN_STRUCT, token_TokenKind_TOKEN_TYPE, token_TokenKind_TOKEN_PACKED, token_TokenKind_TOKEN_SOA, token_TokenKind_TOKEN_ATTR_SOA, token_TokenKind_TOKEN_ATTR_CFG, token_TokenKind_TOKEN_ATTR_REPR_C, token_TokenKind_TOKEN_ATTR_REPR_COMPATIBLE, token_TokenKind_TOKEN_ATTR_ALLOC, token_TokenKind_TOKEN_ATTR_LINK_SECTION, token_TokenKind_TOKEN_ATTR_NAKED, token_TokenKind_TOKEN_ATTR_ENTRY, token_TokenKind_TOKEN_ATTR_USED, token_TokenKind_TOKEN_ATTR_NO_MANGLE, token_TokenKind_TOKEN_ATTR_LINK_NAME, token_TokenKind_TOKEN_ATTR_MAX_STACK, token_TokenKind_TOKEN_ATTR_INTERRUPT, token_TokenKind_TOKEN_ATTR_SEND, token_TokenKind_TOKEN_ATTR_SYNC, token_TokenKind_TOKEN_ATTR_GLOBAL_ALLOCATOR, token_TokenKind_TOKEN_ATTR_COLD, token_TokenKind_TOKEN_ATTR_INLINE_NEVER, token_TokenKind_TOKEN_ATTR_INLINE_ALWAYS, token_TokenKind_TOKEN_ATTR_EXPORT_NAME, token_TokenKind_TOKEN_ATTR_PANIC_HANDLER, token_TokenKind_TOKEN_ATTR_THREAD_LOCAL, token_TokenKind_TOKEN_ATTR_PERCPU, token_TokenKind_TOKEN_ALIGN, token_TokenKind_TOKEN_ENUM, token_TokenKind_TOKEN_GOTO, token_TokenKind_TOKEN_TRAIT, token_TokenKind_TOKEN_IMPL, token_TokenKind_TOKEN_SELF, token_TokenKind_TOKEN_UNDERSCORE, token_TokenKind_TOKEN_IMPORT, token_TokenKind_TOKEN_EXTERN, token_TokenKind_TOKEN_ASYNC, token_TokenKind_TOKEN_AWAIT, token_TokenKind_TOKEN_RUN, token_TokenKind_TOKEN_SPAWN, token_TokenKind_TOKEN_IDENT, token_TokenKind_TOKEN_I32, token_TokenKind_TOKEN_BOOL, token_TokenKind_TOKEN_U8, token_TokenKind_TOKEN_U32, token_TokenKind_TOKEN_U64, token_TokenKind_TOKEN_I64, token_TokenKind_TOKEN_USIZE, token_TokenKind_TOKEN_ISIZE, token_TokenKind_TOKEN_I32X4, token_TokenKind_TOKEN_I32X8, token_TokenKind_TOKEN_I32X16, token_TokenKind_TOKEN_U32X4, token_TokenKind_TOKEN_U32X8, token_TokenKind_TOKEN_U32X16, token_TokenKind_TOKEN_F32X4, token_TokenKind_TOKEN_TRUE, token_TokenKind_TOKEN_FALSE, token_TokenKind_TOKEN_F32, token_TokenKind_TOKEN_F64, token_TokenKind_TOKEN_VOID, token_TokenKind_TOKEN_INT, token_TokenKind_TOKEN_FLOAT, token_TokenKind_TOKEN_LPAREN, token_TokenKind_TOKEN_RPAREN, token_TokenKind_TOKEN_LBRACE, token_TokenKind_TOKEN_RBRACE, token_TokenKind_TOKEN_LBRACKET, token_TokenKind_TOKEN_RBRACKET, token_TokenKind_TOKEN_ARROW, token_TokenKind_TOKEN_FATARROW, token_TokenKind_TOKEN_COMMA, token_TokenKind_TOKEN_COLON, token_TokenKind_TOKEN_DOT, token_TokenKind_TOKEN_DOTDOT, token_TokenKind_TOKEN_ELLIPSIS, token_TokenKind_TOKEN_SEMICOLON, token_TokenKind_TOKEN_PLUS, token_TokenKind_TOKEN_MINUS, token_TokenKind_TOKEN_STAR, token_TokenKind_TOKEN_SLASH, token_TokenKind_TOKEN_PERCENT, token_TokenKind_TOKEN_AMP, token_TokenKind_TOKEN_PIPE, token_TokenKind_TOKEN_CARET, token_TokenKind_TOKEN_LSHIFT, token_TokenKind_TOKEN_RSHIFT, token_TokenKind_TOKEN_PLUS_EQ, token_TokenKind_TOKEN_MINUS_EQ, token_TokenKind_TOKEN_STAR_EQ, token_TokenKind_TOKEN_SLASH_EQ, token_TokenKind_TOKEN_PERCENT_EQ, token_TokenKind_TOKEN_AMP_EQ, token_TokenKind_TOKEN_PIPE_EQ, token_TokenKind_TOKEN_CARET_EQ, token_TokenKind_TOKEN_LSHIFT_EQ, token_TokenKind_TOKEN_RSHIFT_EQ, token_TokenKind_TOKEN_TILDE, token_TokenKind_TOKEN_ASSIGN, token_TokenKind_TOKEN_EQ, token_TokenKind_TOKEN_NE, token_TokenKind_TOKEN_LT, token_TokenKind_TOKEN_GT, token_TokenKind_TOKEN_LE, token_TokenKind_TOKEN_GE, token_TokenKind_TOKEN_AMPAMP, token_TokenKind_TOKEN_PIPEPIPE, token_TokenKind_TOKEN_BANG, token_TokenKind_TOKEN_QUESTION, token_TokenKind_TOKEN_AS, token_TokenKind_TOKEN_AT, token_TokenKind_TOKEN_STRING, token_TokenKind_TOKEN_EXPORT, token_TokenKind_TOKEN_NULL };
struct token_Token {
  int32_t kind;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t * ident;
  int32_t ident_len;
};

enum ast_TypeKind { ast_TypeKind_TYPE_I32, ast_TypeKind_TYPE_BOOL, ast_TypeKind_TYPE_U8, ast_TypeKind_TYPE_U32, ast_TypeKind_TYPE_U64, ast_TypeKind_TYPE_I64, ast_TypeKind_TYPE_USIZE, ast_TypeKind_TYPE_ISIZE, ast_TypeKind_TYPE_NAMED, ast_TypeKind_TYPE_PTR, ast_TypeKind_TYPE_ARRAY, ast_TypeKind_TYPE_SLICE, ast_TypeKind_TYPE_LINEAR, ast_TypeKind_TYPE_VECTOR, ast_TypeKind_TYPE_F32, ast_TypeKind_TYPE_F64, ast_TypeKind_TYPE_VOID };
enum ast_ExprKind { ast_ExprKind_EXPR_LIT, ast_ExprKind_EXPR_FLOAT_LIT, ast_ExprKind_EXPR_BOOL_LIT, ast_ExprKind_EXPR_VAR, ast_ExprKind_EXPR_ADD, ast_ExprKind_EXPR_SUB, ast_ExprKind_EXPR_MUL, ast_ExprKind_EXPR_DIV, ast_ExprKind_EXPR_MOD, ast_ExprKind_EXPR_SHL, ast_ExprKind_EXPR_SHR, ast_ExprKind_EXPR_BITAND, ast_ExprKind_EXPR_BITOR, ast_ExprKind_EXPR_BITXOR, ast_ExprKind_EXPR_EQ, ast_ExprKind_EXPR_NE, ast_ExprKind_EXPR_LT, ast_ExprKind_EXPR_LE, ast_ExprKind_EXPR_GT, ast_ExprKind_EXPR_GE, ast_ExprKind_EXPR_LOGAND, ast_ExprKind_EXPR_LOGOR, ast_ExprKind_EXPR_NEG, ast_ExprKind_EXPR_BITNOT, ast_ExprKind_EXPR_LOGNOT, ast_ExprKind_EXPR_IF, ast_ExprKind_EXPR_BLOCK, ast_ExprKind_EXPR_TERNARY, ast_ExprKind_EXPR_ASSIGN, ast_ExprKind_EXPR_ADD_ASSIGN, ast_ExprKind_EXPR_SUB_ASSIGN, ast_ExprKind_EXPR_MUL_ASSIGN, ast_ExprKind_EXPR_DIV_ASSIGN, ast_ExprKind_EXPR_MOD_ASSIGN, ast_ExprKind_EXPR_BITAND_ASSIGN, ast_ExprKind_EXPR_BITOR_ASSIGN, ast_ExprKind_EXPR_BITXOR_ASSIGN, ast_ExprKind_EXPR_SHL_ASSIGN, ast_ExprKind_EXPR_SHR_ASSIGN, ast_ExprKind_EXPR_BREAK, ast_ExprKind_EXPR_CONTINUE, ast_ExprKind_EXPR_RETURN, ast_ExprKind_EXPR_PANIC, ast_ExprKind_EXPR_MATCH, ast_ExprKind_EXPR_FIELD_ACCESS, ast_ExprKind_EXPR_STRUCT_LIT, ast_ExprKind_EXPR_ARRAY_LIT, ast_ExprKind_EXPR_INDEX, ast_ExprKind_EXPR_CALL, ast_ExprKind_EXPR_METHOD_CALL, ast_ExprKind_EXPR_ENUM_VARIANT, ast_ExprKind_EXPR_ADDR_OF, ast_ExprKind_EXPR_DEREF, ast_ExprKind_EXPR_BINOP, ast_ExprKind_EXPR_AS, ast_ExprKind_EXPR_AWAIT, ast_ExprKind_EXPR_RUN, ast_ExprKind_EXPR_SPAWN, ast_ExprKind_EXPR_TRY_PROPAGATE, ast_ExprKind_EXPR_STRING_LIT };
enum ast_ImportKind { ast_ImportKind_IMPORT_WHOLE, ast_ImportKind_IMPORT_BINDING, ast_ImportKind_IMPORT_SELECT };
struct ast_Type {
  int32_t kind;
  uint8_t name[128];
  int32_t name_len;
  int32_t elem_type_ref;
  int32_t array_size;
  uint8_t region_label[128];
  int32_t region_label_len;
};

struct ast_Expr {
  int32_t kind;
  int32_t resolved_type_ref;
  int32_t line;
  int32_t col;
  int64_t int_val;
  double float_val;
  uint8_t var_name[128];
  int32_t var_name_len;
  int32_t binop_left_ref;
  int32_t binop_right_ref;
  int32_t unary_operand_ref;
  int32_t if_cond_ref;
  int32_t if_then_ref;
  int32_t if_else_ref;
  int32_t block_ref;
  int32_t match_matched_ref;
  int32_t match_arm_base;
  int32_t match_num_arms;
  int32_t field_access_base_ref;
  uint8_t field_access_field_name[128];
  int32_t field_access_field_len;
  int32_t field_access_is_enum_variant;
  int32_t field_access_offset;
  int32_t field_access_soa_stride;
  int32_t index_base_ref;
  int32_t index_index_ref;
  int32_t index_base_is_slice;
  int32_t call_callee_ref;
  int32_t call_arg_base;
  int32_t call_num_args;
  int32_t call_num_type_args;
  int32_t method_call_base_ref;
  uint8_t method_call_name[128];
  int32_t method_call_name_len;
  int32_t method_call_arg_base;
  int32_t method_call_num_args;
  int32_t const_folded_val;
  int32_t const_folded_valid;
  int32_t index_proven_in_bounds;
  uint8_t struct_lit_struct_name[128];
  int32_t struct_lit_struct_name_len;
  int32_t struct_lit_field_base;
  int32_t struct_lit_num_fields;
  int32_t array_lit_elem_base;
  int32_t array_lit_num_elems;
  int32_t float_bits_lo;
  int32_t float_bits_hi;
  int32_t enum_variant_tag;
  int32_t as_operand_ref;
  int32_t as_target_type_ref;
  int32_t call_resolved_func_index;
  int32_t call_resolved_dep_index;
};

struct ast_ConstDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct ast_LetDecl {
  uint8_t name[128];
  int32_t name_len;
  int32_t type_ref;
  int32_t init_ref;
};

struct ast_WhileLoop {
  int32_t cond_ref;
  int32_t body_ref;
};

struct ast_ForLoop {
  int32_t init_ref;
  int32_t cond_ref;
  int32_t step_ref;
  int32_t body_ref;
};

struct ast_IfStmt {
  int32_t cond_ref;
  int32_t then_body_ref;
  int32_t else_body_ref;
};

struct ast_StmtOrderItem {
  uint8_t kind;
  int32_t idx;
};

struct ast_LabeledStmt {
  uint8_t label[128];
  int32_t label_len;
  int32_t is_goto;
  uint8_t goto_target[128];
  int32_t goto_target_len;
  int32_t return_expr_ref;
};

struct ast_Block {
  int32_t const_base;
  int32_t num_consts;
  int32_t let_base;
  int32_t num_lets;
  int32_t num_early_lets;
  int32_t loop_base;
  int32_t num_loops;
  int32_t for_loop_base;
  int32_t num_for_loops;
  int32_t if_base;
  int32_t num_if_stmts;
  int32_t region_base;
  int32_t num_regions;
  int32_t defer_base;
  int32_t num_defers;
  int32_t labeled_base;
  int32_t num_labeled_stmts;
  int32_t expr_stmt_base;
  int32_t num_expr_stmts;
  int32_t final_expr_ref;
  int32_t stmt_order_base;
  int32_t num_stmt_order;
  int32_t parent_block_ref;
};

struct ast_Param {
  uint8_t name[32];
  int32_t name_len;
  int32_t type_ref;
};

struct ast_Func {
  uint8_t name[128];
  int32_t name_len;
  int32_t param_base;
  int32_t num_params;
  int32_t num_generic_params;
  int32_t return_type_ref;
  int32_t body_ref;
  int32_t body_expr_ref;
  int32_t is_extern;
  int32_t is_async;
  int32_t is_used;
  int32_t is_naked;
  int32_t is_entry;
  int32_t is_no_mangle;
  int32_t is_interrupt;
  int32_t abi_kind;
  int32_t is_variadic;
  int32_t is_export;
};

struct ast_StructLayout {
  uint8_t name[128];
  int32_t name_len;
  int32_t field_base;
  int32_t num_fields;
  int32_t allow_padding;
  int32_t soa;
  int32_t packed;
  int32_t repr_compatible;
  int32_t is_export;
};

struct ast_Module {
  int32_t num_funcs;
  int32_t main_func_index;
  int32_t num_imports;
  int32_t num_top_level_lets;
  int32_t num_struct_layouts;
  int32_t pending_allow_padding;
  int32_t pending_soa_struct;
  int32_t pending_cfg_skip;
  int32_t pending_repr_c_struct;
  int32_t pending_repr_compatible_struct;
  int32_t pending_used;
  int32_t pending_naked;
  int32_t pending_entry;
  int32_t pending_no_mangle;
  int32_t pending_interrupt;
  int32_t pending_export;
  int32_t num_module_enums;
};

struct ast_ASTArena {
  int32_t num_types;
  int32_t num_exprs;
  int32_t num_blocks;
  int32_t num_funcs;
};

struct ast_PipelineDepCtx {
  int32_t ndep;
  uint8_t entry_dir_buf[512];
  int32_t entry_dir_len;
  int32_t num_lib_roots;
  uint8_t path_buf[512];
  uint8_t loaded_buf[4194304];
  ssize_t loaded_len;
  uint8_t preprocess_buf[4194304];
  int32_t preprocess_len;
  int32_t use_asm_backend;
  int32_t target_arch;
  int32_t target_cpu_features;
  int32_t use_macho_o;
  int32_t use_coff_o;
  int32_t current_block_ref;
  int32_t typeck_loop_depth;
  int32_t current_func_index;
  int32_t skip_codegen_dep_0;
  int32_t entry_already_parsed;
  int32_t current_func_single_empty_param_index;
  int32_t current_func_empty_param_count;
  int32_t current_emit_empty_var_next_index;
  int32_t emit_expr_as_callee;
  struct ast_Module * current_codegen_module;
  struct ast_ASTArena * current_codegen_arena;
  int32_t current_codegen_dep_index;
  uint8_t current_codegen_prefix_mirror[128];
  int32_t current_codegen_prefix_len;
  int32_t asm_entry_module_only;
  uint8_t entry_module_import_path_mirror[128];
  int32_t entry_module_import_path_len;
  int32_t typeck_scope_region_len;
  uint8_t typeck_scope_region_label[128];
};

struct lexer_Lexer {
  size_t pos;
  int32_t line;
  int32_t col;
};

struct lexer_LexerResult {
  struct lexer_Lexer next_lex;
  struct token_Token tok;
  size_t token_start;
};

struct lexer_Lexer;
struct lexer_LexerResult;
struct token_Token;
struct ast_Type;
struct ast_Expr;
struct ast_ConstDecl;
struct ast_LetDecl;
struct ast_WhileLoop;
struct ast_ForLoop;
struct ast_IfStmt;
struct ast_StmtOrderItem;
struct ast_LabeledStmt;
struct ast_Block;
struct ast_Param;
struct ast_Func;
struct ast_StructLayout;
struct ast_Module;
struct ast_ASTArena;
struct ast_PipelineDepCtx;
extern int token_is_eof(struct token_Token t);
int token_is_eof(struct token_Token t) {
  return 0;
}
extern int32_t cfg_eval_expr_c(uint8_t * start, int32_t len);
extern struct xlang_slice_uint8_t lexer_parser_slice_from_buf(uint8_t * data, int32_t len);
extern struct lexer_Lexer lexer_init(void);
extern struct lexer_Lexer lexer_advance_one(struct lexer_Lexer lex, uint8_t c);
extern int lexer_is_alpha(uint8_t c);
extern int lexer_is_hex_digit(uint8_t c);
extern int32_t lexer_hex_digit_value(uint8_t c);
extern int lexer_is_digit(uint8_t c);
extern int lexer_is_alnum_underscore(uint8_t c);
extern int lexer_match_keyword(struct xlang_slice_uint8_t * data, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword);
extern int lexer_match_keyword_buf(uint8_t * data, int32_t data_len, size_t start, int32_t len, struct xlang_slice_uint8_t * keyword);
extern struct token_Token lexer_try_keyword(struct xlang_slice_uint8_t * data, size_t start, size_t len, int32_t line0, int32_t col0);
extern struct token_Token lexer_try_keyword_buf(uint8_t * data, int32_t data_len, size_t start, size_t len, int32_t line0, int32_t col0);
extern struct lexer_Lexer lexer_skip_repr_c_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern struct lexer_Lexer lexer_skip_cfg_attr_if_present(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_cfg_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_repr_c_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_repr_compatible_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_soa_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_alloc_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_used_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_naked_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_entry_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_no_mangle_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_interrupt_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_send_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern int32_t lexer_try_sync_attr_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern struct lexer_Lexer lexer_skip_whitespace_and_comments(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern struct lexer_Lexer lexer_skip_whitespace_and_comments_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_LexerResult lexer_next(struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern void lexer_apply_optional_exponent(struct lexer_Lexer l, struct xlang_slice_uint8_t * data, double fval, struct lexer_Lexer * out_l, double * out_f);
extern void lexer_next_body_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data);
extern void lexer_next_punct_into(struct lexer_LexerResult * out, struct lexer_Lexer l, struct xlang_slice_uint8_t * data, uint8_t c);
extern void lexer_write_next_lex_into(struct lexer_LexerResult * out, struct lexer_Lexer l);
extern void lexer_write_tok_into(struct lexer_LexerResult * out, struct token_Token t);
extern void lexer_next_impl(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern void lexer_next_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * data);
extern void lexer_next_buf_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_LexerResult lexer_next_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t lexer_main(void);
extern int token_is_eof(struct token_Token t);
extern void ast_ast_pool_block_on_alloc(struct ast_ASTArena * arena, int32_t block_ref);
extern int32_t pipeline_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_block_alloc(struct ast_ASTArena * arena);
extern int32_t pipeline_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Type pipeline_arena_type_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_type_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern struct ast_Expr pipeline_arena_expr_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_expr_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block pipeline_arena_block_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_block_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern struct ast_Func pipeline_arena_func_get_copy(struct ast_ASTArena * arena, int32_t ref);
extern void pipeline_arena_func_set_copy(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
extern int32_t pipeline_arena_type_cap(void);
extern int32_t pipeline_arena_expr_cap(void);
extern int32_t pipeline_arena_block_cap(void);
extern int32_t pipeline_arena_func_cap(void);
extern int32_t pipeline_module_import_alloc(struct ast_Module * module);
extern void pipeline_module_import_set_path(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_path_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_path_copy(struct ast_Module * module, int32_t idx, uint8_t * dst, int32_t dst_cap);
extern uint8_t pipeline_module_import_path_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_kind(struct ast_Module * module, int32_t idx, int32_t kind);
extern int32_t pipeline_module_import_kind_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_binding_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_binding_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_import_binding_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_import_set_select_count(struct ast_Module * module, int32_t idx, int32_t n);
extern int32_t pipeline_module_import_append_select_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_count_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_import_set_select_name(struct ast_Module * module, int32_t idx, int32_t sel, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_import_select_name_len(struct ast_Module * module, int32_t idx, int32_t sel);
extern uint8_t pipeline_module_import_select_name_byte_at(struct ast_Module * module, int32_t idx, int32_t sel, int32_t off);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t li, int32_t j, uint8_t * fname_bytes, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_name_into(struct ast_Module * module, int32_t idx, uint8_t * out64);
extern void pipeline_module_struct_layout_field_name_into(struct ast_Module * module, int32_t li, int32_t j, uint8_t * out64);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t idx, int32_t nf);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_top_level_let_alloc(struct ast_Module * module);
extern void pipeline_module_top_level_let_set(struct ast_Module * module, int32_t idx, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref, int32_t is_const);
extern int32_t pipeline_module_top_level_let_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_top_level_let_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern int32_t pipeline_module_top_level_let_type_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_init_ref(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_top_level_let_is_const(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_enum_alloc(struct ast_Module * module);
extern void pipeline_module_enum_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_enum_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_allow_padding_at(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern void pipeline_module_struct_layout_set_packed(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_struct_layout_packed_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_soa_at(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_field_offset_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_field_offset(struct ast_Module * module, int32_t li, int32_t j, int32_t foff);
extern int32_t pipeline_onefunc_append_const_name(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val);
extern int32_t pipeline_onefunc_const_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_const_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_const_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_consts(uint8_t * out);
extern int32_t pipeline_onefunc_append_let(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t pipeline_onefunc_let_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_let_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern int32_t pipeline_onefunc_let_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_type_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_lets(uint8_t * out);
extern void pipeline_onefunc_const_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_let_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_copy_sidecar(uint8_t * dst, uint8_t * src);
extern void ast_ast_pool_onefunc_reset(uint8_t * out);
extern int32_t pipeline_block_append_const(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_let(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_if(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_block_append_region(struct ast_ASTArena * arena, int32_t br, uint8_t * label, int32_t label_len, int32_t body_ref);
extern int32_t pipeline_block_append_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t body_ref);
extern int32_t pipeline_block_region_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ri);
extern int32_t pipeline_block_append_expr_stmt(struct ast_ASTArena * arena, int32_t br, int32_t expr_ref);
extern int32_t pipeline_block_append_stmt_order(struct ast_ASTArena * arena, int32_t br, uint8_t kind, int32_t idx);
extern int32_t pipeline_block_const_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern int32_t pipeline_block_const_name_len(struct ast_ASTArena * arena, int32_t br, int32_t ci);
extern void pipeline_block_const_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t ci, uint8_t * dst);
extern int32_t pipeline_block_let_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_type_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_block_let_name_len(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern void pipeline_block_let_name_copy64(struct ast_ASTArena * arena, int32_t br, int32_t li, uint8_t * dst);
extern int32_t pipeline_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t br, int32_t ei);
extern uint8_t pipeline_block_stmt_order_kind(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_stmt_order_idx(struct ast_ASTArena * arena, int32_t br, int32_t si);
extern int32_t pipeline_block_if_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_then_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_if_else_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t ii);
extern int32_t pipeline_block_resolve_var_type_ref(struct ast_ASTArena * arena, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void pipeline_block_fill_ifs_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_stmt_order_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_expr_stmts_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_while(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_block_append_for(struct ast_ASTArena * arena, int32_t br, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_block_while_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_while_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t wi);
extern int32_t pipeline_block_for_init_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_cond_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_step_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern int32_t pipeline_block_for_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t fi);
extern void pipeline_block_fill_whiles_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_fors_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_labeled(struct ast_ASTArena * arena, int32_t br, int32_t label_len, int32_t is_goto, int32_t goto_target_len, int32_t return_expr_ref);
extern int32_t pipeline_block_labeled_return_expr_ref(struct ast_ASTArena * arena, int32_t br, int32_t li);
extern int32_t pipeline_onefunc_append_while(uint8_t * out, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_while_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_while_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_whiles(uint8_t * out);
extern int32_t pipeline_onefunc_append_for(uint8_t * out, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_for_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_step_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_for_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_fors(uint8_t * out);
extern void pipeline_dep_ctx_set_module(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_Module * m);
extern void pipeline_dep_ctx_set_arena(struct ast_PipelineDepCtx * ctx, int32_t idx, struct ast_ASTArena * a);
extern struct ast_Module * pipeline_dep_ctx_module_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern struct ast_ASTArena * pipeline_dep_ctx_arena_at(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern void pipeline_dep_ctx_set_import_path(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_dep_ctx_import_path_len(struct ast_PipelineDepCtx * ctx, int32_t idx);
extern uint8_t pipeline_dep_ctx_import_path_byte_at(struct ast_PipelineDepCtx * ctx, int32_t idx, int32_t off);
extern void pipeline_dep_ctx_import_path_copy64(struct ast_PipelineDepCtx * ctx, int32_t idx, uint8_t * dst);
extern int32_t pipeline_dep_ctx_ndep(struct ast_PipelineDepCtx * ctx);
extern void pipeline_dep_ctx_set_ndep(struct ast_PipelineDepCtx * ctx, int32_t n);
extern int32_t pipeline_ctx_append_lib_root(struct ast_PipelineDepCtx * ctx, uint8_t * path, int32_t len);
extern int32_t pipeline_ctx_lib_root_count(struct ast_PipelineDepCtx * ctx);
extern int32_t pipeline_ctx_lib_root_len(struct ast_PipelineDepCtx * ctx, int32_t i);
extern void pipeline_ctx_lib_root_copy(struct ast_PipelineDepCtx * ctx, int32_t i, uint8_t * dst, int32_t cap);
extern int32_t pipeline_module_func_alloc_slot(struct ast_Module * module);
extern int32_t pipeline_module_func_ref_at(struct ast_Module * module, int32_t func_index);
extern void pipeline_module_func_ref_set(struct ast_Module * module, int32_t func_index, int32_t func_ref);
extern void pipeline_module_func_set_return_type(struct ast_Module * module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(struct ast_Module * module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(struct ast_Module * module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(struct ast_Module * module, int32_t fi, int32_t is_extern);
extern void pipeline_module_func_set_is_variadic(struct ast_Module * module, int32_t fi, int32_t is_variadic);
extern int32_t pipeline_module_func_is_variadic_at(struct ast_Module * module, int32_t fi);
extern void pipeline_module_func_set_num_params(struct ast_Module * module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_num_generic_params(struct ast_Module * module, int32_t fi, int32_t n);
extern int32_t pipeline_module_func_return_type_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_num_generic_params_at(struct ast_Module * module, int32_t fi);
extern int32_t pipeline_module_func_name_equal_at(struct ast_Module * module, int32_t fi, uint8_t * name, int32_t name_len);
extern uint8_t pipeline_module_func_name_byte_at(struct ast_Module * module, int32_t fi, int32_t i);
extern int32_t pipeline_module_func_body_expr_ref_at(struct ast_Module * module, int32_t fi);
extern int ast_ref_is_null(int32_t ref);
extern int32_t ast_ast_placeholder(void);
extern void ast_expr_layout_prime_call_resolved(void);
extern void ast_func_layout_prime_generic_params(void);
extern void ast_ast_arena_init(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_type_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_expr_alloc(struct ast_ASTArena * arena);
extern int32_t ast_ast_arena_block_alloc(struct ast_ASTArena * arena);
extern struct ast_Type ast_ast_arena_type_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_type_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Type t);
extern void ast_expr_init_match_enum(struct ast_Expr * e);
extern int32_t pipeline_expr_append_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_call_num_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_call_num_type_args_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_append_method_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern int32_t pipeline_expr_method_call_arg_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_append_match_arm(struct ast_ASTArena * arena, int32_t expr_ref, int32_t result_ref, int32_t is_wildcard, int32_t lit_val, int32_t is_enum_variant, int32_t variant_index);
extern int32_t pipeline_expr_match_num_arms_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern int32_t pipeline_expr_match_arm_result_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_is_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern int32_t pipeline_expr_match_arm_variant_index(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i);
extern void pipeline_expr_match_arm_set_wildcard(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_lit_val(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t v);
extern void pipeline_expr_match_arm_set_enum_variant(struct ast_ASTArena * arena, int32_t expr_ref, int32_t i, int32_t is_var, int32_t variant_index);
extern int32_t pipeline_expr_append_struct_lit_field(struct ast_ASTArena * arena, int32_t expr_ref, uint8_t * name_bytes, int32_t name_len, int32_t init_ref);
extern int32_t pipeline_expr_append_array_lit_elem(struct ast_ASTArena * arena, int32_t expr_ref, int32_t elem_ref);
extern int32_t pipeline_expr_array_lit_elem_ref(struct ast_ASTArena * arena, int32_t expr_ref, int32_t idx);
extern int32_t pipeline_expr_array_lit_num_elems_at(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_init_call_resolve_at_ref(struct ast_ASTArena * arena, int32_t expr_ref);
extern void pipeline_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern void ast_expr_init_call_resolve(struct ast_ASTArena * arena, int32_t expr_ref);
extern void ast_ast_expr_apply_call_resolve(struct ast_ASTArena * arena, int32_t call_expr_ref, int32_t dep_ix, int32_t func_ix);
extern struct ast_Expr ast_ast_arena_expr_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_expr_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Expr e);
extern struct ast_Block ast_ast_arena_block_get(struct ast_ASTArena * arena, int32_t ref);
extern int ast_ast_name_bytes_equal(uint8_t * a_nm, int32_t a_len, uint8_t * b_nm, int32_t b_len);
extern int32_t ast_ast_block_final_expr_ref(struct ast_ASTArena * a, int32_t body_ref);
extern int implicit_tail_expr_disallowed_by_glue(struct ast_ASTArena * a, int32_t expr_ref);
extern int ast_ast_expr_disallows_implicit_tail(struct ast_ASTArena * a, int32_t expr_ref);
extern int32_t ast_ast_block_num_consts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_lets(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_for_loops(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_if_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_regions(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_region_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ri);
extern int32_t ast_ast_block_num_expr_stmts(struct ast_ASTArena * a, int32_t br);
extern int32_t ast_ast_block_num_stmt_order(struct ast_ASTArena * a, int32_t br);
extern uint8_t ast_ast_block_stmt_order_kind(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_stmt_order_idx(struct ast_ASTArena * a, int32_t br, int32_t si);
extern int32_t ast_ast_block_const_init_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_const_type_ref(struct ast_ASTArena * a, int32_t br, int32_t ci);
extern int32_t ast_ast_block_let_init_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_let_type_ref(struct ast_ASTArena * a, int32_t br, int32_t li);
extern int32_t ast_ast_block_expr_stmt_ref(struct ast_ASTArena * a, int32_t br, int32_t ei);
extern int32_t ast_ast_block_while_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_while_body_ref(struct ast_ASTArena * a, int32_t br, int32_t wi);
extern int32_t ast_ast_block_for_init_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_step_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_for_body_ref(struct ast_ASTArena * a, int32_t br, int32_t fi);
extern int32_t ast_ast_block_if_cond_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_then_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_if_else_body_ref(struct ast_ASTArena * a, int32_t br, int32_t ii);
extern int32_t ast_ast_block_resolve_var_to_type_ref(struct ast_ASTArena * a, int32_t block_ref, uint8_t * vname, int32_t vlen);
extern void ast_ast_arena_patch_block_parent_links(struct ast_ASTArena * arena, int32_t block_ref, int32_t parent_ref);
extern void ast_ast_arena_block_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Block b);
extern int32_t ast_ast_arena_func_alloc(struct ast_ASTArena * arena);
extern struct ast_Func ast_ast_arena_func_get(struct ast_ASTArena * arena, int32_t ref);
extern void ast_ast_arena_func_set(struct ast_ASTArena * arena, int32_t ref, struct ast_Func f);
struct parser_OneFuncResult {
  int ok;
  struct lexer_Lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  int32_t num_params;
  int32_t num_generic_params;
  int32_t num_consts;
  int32_t num_lets;
  int has_if_expr;
  int if_cond_true;
  int32_t if_then_val;
  int32_t if_else_val;
  int32_t if_cond_expr_ref;
  int has_mul;
  int32_t mul_right_val;
  int has_binop;
  int32_t binop_right_val;
  int32_t binop_left_param_idx;
  int32_t binop_right_param_idx;
  int has_unary_neg;
  int32_t return_val;
  int has_call_expr;
  uint8_t call_callee_name[128];
  int32_t call_callee_len;
  uint8_t return_var_name[128];
  int32_t return_var_name_len;
  int32_t return_expr_ref;
  int has_final_expr;
  int has_explicit_return_kw;
  int32_t call_num_args;
  int32_t num_loops;
  int32_t num_for_loops;
  int32_t num_if_stmts;
  int32_t num_src_stmt_order;
  int32_t num_src_body_expr_stmts;
  int32_t func_return_type_ref;
  /* Cap 10.7.1 language: 1 when param list ends with `, ...` (≡ parser.x). */
  int32_t is_variadic;
};

struct parser_ParseResult {
  int ok;
  int32_t return_val;
};

struct parser_ParseIntoResult {
  int32_t ok;
  int32_t main_idx;
};

struct parser_TopLevelLetResult {
  int ok;
  struct lexer_Lexer next_lex;
};

struct parser_TypeAliasResult {
  int ok;
  struct lexer_Lexer next_lex;
};

struct parser_CollectImportsResult {
  struct lexer_Lexer lex;
};

struct parser_ParseExprResult {
  int ok;
  int32_t expr_ref;
  struct lexer_Lexer next_lex;
};

struct parser_ParseBlockResult {
  int ok;
  int32_t block_ref;
  struct lexer_Lexer next_lex;
};

struct parser_ExternParseResult {
  struct lexer_Lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  int32_t return_ty_ref;
  int32_t num_params;
  int32_t abi_kind;
  int32_t is_variadic;
};

struct parser_TrySkipAllowResult {
  struct lexer_Lexer lex;
  int32_t skipped;
  uint8_t _pad[4];
};

struct parser_LibraryParseResult {
  int ok;
  uint8_t _pad[4];
  struct lexer_Lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  uint8_t _pad_tail[4];
};

struct parser_LibraryParseScanResult {
  int ok;
  uint8_t _pad[4];
  struct lexer_Lexer next_lex;
  uint8_t name[128];
  int32_t name_len;
  uint8_t param_name[128];
  int32_t param_name_len;
  uint8_t param_type_name[128];
  int32_t param_type_len;
  uint8_t field_name[128];
  int32_t field_len;
  uint8_t _pad_tail[4];
  uint8_t _pad_tail2[4];
};

extern int32_t parser_parse_peek_function_name_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, uint8_t * out);
extern void parser_pipeline_module_reset_parse_counters(struct ast_Module * module);
extern uint8_t * parser_onefunc_result_pool_ptr(struct parser_OneFuncResult * res);
extern void parser_copy_lex_from_import_into(struct lexer_Lexer * out, struct parser_CollectImportsResult res);
extern void parser_lex_from_next_into(struct lexer_Lexer * out, struct lexer_LexerResult r);
extern void parser_lex_from_result_ptr_into(struct lexer_Lexer * out_lex, struct lexer_LexerResult * r);
extern void parser_lexer_copy_into(struct lexer_Lexer * out_lex, struct lexer_Lexer src_lex);
extern void parser_lexer_copy_from_parse_expr_result_into(struct lexer_Lexer * out_lex, struct parser_ParseExprResult * res);
extern void parser_parse_expr_result_reset(struct parser_ParseExprResult * out_res, struct lexer_Lexer next_lex);
extern void parser_rewind_lex_for_following_stmt_into(struct lexer_Lexer * out_lex, struct lexer_Lexer lex_in, struct lexer_LexerResult r);
extern void parser_lex_from_onefunc_next_into(struct lexer_Lexer * out, struct parser_OneFuncResult * res);
extern size_t parser_lexer_pos_before_run(size_t end_pos, int32_t run_len);
extern int32_t parser_lexer_token_run_len(enum token_TokenKind kind);
extern struct lexer_Lexer parser_lex_at_token_from_result(struct lexer_LexerResult r);
extern struct lexer_Lexer parser_rewind_lex_for_following_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r);
extern struct lexer_Lexer parser_realign_lex_after_compound_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r_in, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_rewind_lex_for_lparen_control_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r_in, struct xlang_slice_uint8_t * source);
extern int parser_match_kw_immediately_before(struct xlang_slice_uint8_t * source, size_t ident_start);
extern int parser_return_kw_immediately_before(struct xlang_slice_uint8_t * source, size_t ident_start);
extern int parser_match_kw_immediately_before_buf(uint8_t * data, int32_t len, size_t ident_start);
extern int32_t parser_advance_past_stmt_semicolon_into(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern int32_t parser_advance_past_stmt_semicolon_into_buf(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t parser_advance_past_cond_rparen_into(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern int32_t parser_advance_past_cond_rparen_into_buf(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_onefunc_result_layout_prime(void);
extern void parser_set_onefunc_fail(struct parser_OneFuncResult * out, struct lexer_Lexer next_lex);
extern int parser_onefunc_finish_after_return_lex(struct parser_OneFuncResult * out, struct parser_OneFuncResult * impl_snap, struct xlang_slice_uint8_t * source, struct lexer_Lexer lex_after_expr, uint8_t * func_name, int32_t func_name_len, int32_t return_expr_ref);
extern void parser_onefunc_result_layout_prime_b(void);
extern void parser_onefunc_result_layout_prime_c(void);
extern void parser_onefunc_result_layout_prime_d(void);
extern void parser_onefunc_result_layout_prime_d_b(void);
extern void parser_onefunc_result_layout_prime_e(void);
extern void parser_onefunc_result_layout_prime_f(void);
extern void parser_copy_onefunc_into(struct parser_OneFuncResult * dst, struct parser_OneFuncResult * src);
extern struct parser_OneFuncResult parser_onefunc_scratch_empty(void);
extern void parser_onefunc_merge_pool_out_to_snap(struct parser_OneFuncResult * snap, struct parser_OneFuncResult * out);
extern void parser_onefunc_finish_impl_to_out(struct parser_OneFuncResult * out, struct parser_OneFuncResult * snap, struct lexer_Lexer lex, uint8_t * name, int32_t name_len, int32_t ret_expr_storage);
extern void parser_onefunc_res_wire_dummy_head(struct parser_OneFuncResult * res, struct lexer_Lexer lex, uint8_t * name64);
extern void parser_onefunc_res_wire_dummy_const_let(struct parser_OneFuncResult * res);
extern void parser_onefunc_res_wire_dummy_if_mul(struct parser_OneFuncResult * res);
extern void parser_onefunc_res_wire_dummy_call_binop(struct parser_OneFuncResult * res, uint8_t * name64);
extern void parser_onefunc_res_wire_dummy_loop_call(struct parser_OneFuncResult * res);
extern void parser_onefunc_res_wire_dummy_for_if(struct parser_OneFuncResult * res);
extern struct parser_OneFuncResult parser_onefunc_alloc_wired_for_parse(struct lexer_Lexer lex);
extern void parser_onefunc_snap_set_return_path(struct parser_OneFuncResult * snap, int has_call, uint8_t * ret_var, int32_t ret_var_len, int32_t ret_expr_ref);
extern void parser_onefunc_push_src_stmt(struct parser_OneFuncResult * out, uint8_t kind, int32_t idx);
extern void parser_expr_set_common_zeros(struct ast_Expr * e);
extern int32_t parser_alloc_true_bool_lit(struct ast_ASTArena * arena);
extern int32_t parser_alloc_float_lit(struct ast_ASTArena * arena, double fval);
extern int32_t parser_alloc_int_lit(struct ast_ASTArena * arena, int64_t ival);
extern 
/* wave305 Cap residual pure: full i64 EXPR_LIT (plain let/return must not use i32 sidecar). */
int32_t parser_alloc_int_lit(struct ast_ASTArena * arena, int64_t ival) {
  {
    int32_t ref = ast_ast_arena_expr_alloc(arena);
    if ((ref ==0)) {
      return 0;
    }
    struct ast_Expr e = ast_ast_arena_expr_get(arena, ref);
    (void)(((e.kind) = 0));
    (void)(((e.int_val) = ival));
    (void)(((e.line) = 0));
    (void)(((e.col) = 0));
    (void)(parser_expr_set_common_zeros(&(e)));
    (void)(ast_ast_arena_expr_set(arena, ref, e));
    return ref;
  }
}
int32_t parser_expr_wrap_in_return(struct ast_ASTArena * arena, int32_t type_ref, int32_t inner_ref);
extern int parser_should_wrap_func_tail_in_return(struct ast_ASTArena * arena, struct parser_OneFuncResult * res, int32_t type_ref);
extern void parser_parse_match_subject_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_match_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_at_simd_builtin_into(struct ast_ASTArena * arena, struct lexer_LexerResult r0, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_primary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_as_suffix_into(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_unary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_cast_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_term_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_addsub_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_shift_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_relcompare_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_compare_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_bitand_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_bitxor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_bitor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_logand_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_logor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_ternary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern int parser_is_compound_assign_token(enum token_TokenKind kind);
extern enum ast_ExprKind parser_compound_assign_token_to_expr_kind(enum token_TokenKind kind);
extern int parser_expr_ref_is_assign_lvalue(struct ast_ASTArena * arena, int32_t expr_ref);
extern void parser_parse_assign_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_finish_struct_lit_from_type_ident_into(struct ast_ASTArena * arena, int32_t lit_ref, struct lexer_Lexer lex_in_brace, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_cond_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_expr_with_leading_int_as_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
extern void parser_parse_expr_with_leading_int_as_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern int parser_fill_block_const_let_from_res(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t type_ref);
extern int parser_append_block_lets_from_res(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t let_base, int32_t type_ref);
extern int parser_parse_if_stmt_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, int32_t * out_cond, int32_t * out_then, int32_t * out_else, struct lexer_Lexer * lex_out);
extern void parser_parse_block_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseBlockResult * out);
extern int32_t parser_wrap_block_ref_as_expr(struct ast_ASTArena * arena, int32_t block_ref, int32_t type_ref);
/* Final-if zero-re-parse conversion (defined below; static). PLATFORM: SHARED. */
static int32_t parser_if_stmt_parts_to_if_expr(struct ast_ASTArena * arena, int32_t cond_ref, int32_t then_blk, int32_t else_blk, int32_t type_ref);
extern void parser_parse_if_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseExprResult * out);
extern struct parser_ParseResult parser_parse(struct xlang_slice_uint8_t * source);
extern int32_t parser_first_token_kind(struct xlang_slice_uint8_t * source);
extern int32_t parser_first_token_kind_buf(uint8_t * data, int32_t len);
extern int32_t parser_diag_first_ident_len(struct xlang_slice_uint8_t * source);
extern int32_t parser_diag_first_ident_len_buf(uint8_t * data, int32_t len);
extern void parser_diag_skip_let_const_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_diag_skip_let_const(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_diag_skip_let_const_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_diag_skip_let_const_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_body_skip_let_const_then_if_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern int32_t parser_parse_body_let_bracket_compound_init_ref(struct ast_ASTArena * arena, size_t bracket_start, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out, struct lexer_LexerResult * r_out);
extern int32_t parser_parse_type_ref_for_arena_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex);
extern int parser_parse_body_lets_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_OneFuncResult * out, struct lexer_Lexer * lex_out);
extern struct lexer_LexerResult parser_body_skip_let_const_then_if(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_body_skip_let_const_then_if_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_body_skip_let_const_then_if_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_balanced_parens(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_balanced_parens_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_balanced_parens_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_balanced_parens_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_balanced_braces(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_balanced_braces_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_balanced_braces_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_balanced_braces_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_function_full_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_top_level_const_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_top_level_const_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_top_level_let_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_top_level_let_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_function_full(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_function_full_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_function_full_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_LexerResult parser_skip_one_if_core(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_skip_one_if_statement(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_if_statement_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_if_core_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_skip_one_if_core_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_LexerResult parser_skip_one_if_statement_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_if_core_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_if_statement_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_diag_lex_after_imports(struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_diag_lex_after_imports_buf(uint8_t * data, int32_t len);
extern struct lexer_LexerResult parser_diag_after_imports_then_structs(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_LexerResult parser_diag_after_imports_then_structs_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t parser_diag_fail_at_token_kind(struct xlang_slice_uint8_t * source);
extern int32_t parser_diag_fail_at_token_kind_buf(uint8_t * data, int32_t len);
extern struct parser_ParseIntoResult parser_parse_into_result_empty_module_or_fail_tok(int32_t fail_tok);
extern void parser_copy_slice_to_name64(struct xlang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_name64_at_end(struct xlang_slice_uint8_t * source, size_t end_pos, int32_t nlen, uint8_t * out);
extern int32_t parser_struct_field_name_from_tok(struct lexer_LexerResult r, struct xlang_slice_uint8_t * source, uint8_t * out);
extern int32_t parser_struct_field_name_from_tok_buf(struct lexer_LexerResult r, uint8_t * data, int32_t len, uint8_t * out);
extern int parser_struct_field_name_tok_kind(enum token_TokenKind k);
extern int parser_struct_field_continues_tok_kind(enum token_TokenKind k);
extern int parser_token_is_label_start(struct lexer_LexerResult r, struct xlang_slice_uint8_t * source);
extern void parser_copy_slice_to_param32(struct xlang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_param32_at_end(struct xlang_slice_uint8_t * source, size_t end_pos, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_name64_buf(uint8_t * source, int32_t source_len, size_t start, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_name64_at_end_buf(uint8_t * source, int32_t source_len, size_t end_pos, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_param32_at_end_buf(uint8_t * source, int32_t source_len, size_t end_pos, int32_t nlen, uint8_t * out);
extern void parser_copy_slice_to_param32_buf(uint8_t * source, int32_t source_len, size_t start, int32_t nlen, uint8_t * out);
extern void parser_parse_one_function_impl(struct parser_OneFuncResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern int32_t parser_import_path_dot_segment_len(enum token_TokenKind kind, int32_t ident_len);
extern void parser_import_path_dot_segment_copy(struct xlang_slice_uint8_t * source, size_t token_start, int32_t seg_len, uint8_t * path_buf, int32_t path_len);
extern void parser_import_path_dot_segment_copy_buf(uint8_t * data, int32_t len, size_t token_start, int32_t seg_len, uint8_t * path_buf, int32_t path_len);
extern void parser_parse_into_init(struct ast_Module * module, struct ast_ASTArena * arena);
extern struct lexer_Lexer parser_skip_imports(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_imports_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_collect_imports(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct ast_Module * module, struct parser_CollectImportsResult * out);
extern void parser_collect_imports_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, struct ast_Module * module, struct parser_CollectImportsResult * out);
extern void parser_skip_one_struct_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_one_struct(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern int32_t parser_module_try_register_enum_name(struct ast_Module * module, uint8_t * name, int32_t name_len);
extern void parser_module_append_enum_variants_and_skip_body_into(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_module_append_enum_variants_and_skip_body_into_buf(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_enum_register_into(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_enum_register_into_buf(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_enum_register_buf(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_enum_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_one_enum(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_trait_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_one_trait(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_impl_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_one_impl(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_one_enum_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_enum_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_trait_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_trait_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_impl_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_impl_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_extern_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct lexer_Lexer parser_skip_one_extern(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern uint8_t * parser_extern_parse_pool_ptr(struct parser_ExternParseResult * res);
extern void parser_write_extern_params_to_pools(struct ast_ASTArena * arena, struct ast_Module * module, int32_t func_ref, int32_t fi, struct parser_ExternParseResult * res);
extern void parser_extern_parse_set_fail(struct parser_ExternParseResult * out, struct lexer_Lexer lex);
extern void parser_parse_one_extern_skip_into(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_parse_one_extern_skip_into_buf(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t parser_module_register_arena_func(struct ast_Module * module, int32_t func_ref, struct ast_Func f);
extern void parser_parse_one_extern_and_add_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out);
extern void parser_skip_one_extern_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_extern_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_parse_one_extern_and_add_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out);
extern void parser_lex_from_try_skip_into(struct lexer_Lexer * out, struct parser_TrySkipAllowResult t);
extern void parser_lex_from_library_into(struct lexer_Lexer * out, struct parser_LibraryParseResult lib);
extern struct lexer_Lexer parser_lex_from_try_skip(struct parser_TrySkipAllowResult t);
extern struct lexer_Lexer parser_lex_from_library(struct parser_LibraryParseResult lib);
extern int parser_parse_one_function_library_scan(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_LibraryParseScanResult * result);
extern int parser_struct_layout_name_exists_arr(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int32_t parser_struct_layout_first_name_match_idx(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern int32_t parser_struct_layout_placeholder_idx(struct ast_Module * module, uint8_t * nm, int32_t nlen);
extern struct parser_LibraryParseResult parser_parse_one_function_library(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct parser_LibraryParseResult parser_parse_one_function_library_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow(struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source);
extern struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow_buf(struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len);
extern struct parser_TrySkipAllowResult parser_try_skip_allow_padding_struct(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern struct parser_TrySkipAllowResult parser_try_skip_allow_padding_struct_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_one_struct_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct lexer_Lexer parser_skip_one_struct_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t parser_consume_qualified_type_ident_name(struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r, uint8_t * out, int32_t * out_len);
extern int32_t parser_consume_qualified_type_ident_name_buf(uint8_t * data, int32_t len, struct lexer_LexerResult * r, uint8_t * out, int32_t * out_len);
extern int parser_is_pointee_type_token(enum token_TokenKind kind);
extern int32_t parser_alloc_pointee_type_ref_from_tok(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r);
extern int32_t parser_alloc_vector_type_ref(struct ast_ASTArena * arena, int32_t elem_ord, int32_t lanes);
extern int32_t parser_vector_type_ref_from_ident_spelling(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult r);
extern int32_t parser_parse_struct_record_layout_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex, int32_t allow_pad, int32_t force_soa, int32_t repr_compat);
extern void parser_parse_one_function_buf_into(struct parser_OneFuncResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_parse_one_function_library_into(struct parser_LibraryParseResult * out, struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_parse_one_function_library_into_buf(struct parser_LibraryParseResult * out, struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_parse_into_try_skip_allow_into(struct parser_TrySkipAllowResult * out, struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source);
extern void parser_parse_into_try_skip_allow_into_buf(struct parser_TrySkipAllowResult * out, struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len);
extern struct parser_ParseIntoResult parser_parse_into(struct ast_ASTArena * arena, struct ast_Module * module, struct xlang_slice_uint8_t * source);
extern void parser_parse_one_top_level_let_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, int is_const, struct parser_TopLevelLetResult * out);
extern void parser_parse_one_type_alias_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_TypeAliasResult * out);
extern void parser_parse_primary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_unary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_cast_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_term_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_addsub_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_shift_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_relcompare_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_compare_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_bitand_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_bitxor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_bitor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_logand_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_logor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_ternary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_assign_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_finish_struct_lit_from_type_ident_into_buf(struct ast_ASTArena * arena, int32_t lit_ref, struct lexer_Lexer lex_in_brace, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_cond_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern int parser_parse_if_stmt_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, uint8_t * data, int32_t len, int32_t type_ref, int32_t * out_cond, int32_t * out_then, int32_t * out_else, struct lexer_Lexer * lex_out);
extern void parser_parse_block_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, uint8_t * data, int32_t len, int32_t type_ref, struct parser_ParseBlockResult * out);
extern void parser_parse_if_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, uint8_t * data, int32_t len, int32_t type_ref, struct parser_ParseExprResult * out);
extern void parser_parse_match_subject_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_match_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_at_simd_builtin_into_buf(struct ast_ASTArena * arena, struct lexer_LexerResult r0, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern void parser_parse_as_suffix_into_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct parser_ParseExprResult * out);
extern int32_t parser_parse_type_ref_for_arena_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * out_lex);
extern int32_t parser_parse_body_let_bracket_compound_init_ref_buf(struct ast_ASTArena * arena, size_t bracket_start, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out, struct lexer_LexerResult * r_out);
extern int32_t parser_parse_struct_record_layout_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * out_lex, int32_t allow_pad, int32_t force_soa, int32_t repr_compat);
extern int parser_parse_one_function_library_scan_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_LibraryParseScanResult * result);
extern int32_t parser_alloc_pointee_type_ref_from_tok_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct lexer_LexerResult * r);
extern int32_t parser_vector_type_ref_from_ident_spelling_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct lexer_LexerResult r);
extern void parser_parse_one_top_level_let_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, int is_const, struct parser_TopLevelLetResult * out);
extern void parser_parse_one_type_alias_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_TypeAliasResult * out);
extern void parser_skip_balanced_parens_slice_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_skip_balanced_braces_slice_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_module_append_enum_variants_and_skip_body_slice_into_buf(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_parse_one_extern_skip_buf(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern void parser_parse_one_extern_and_add_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out);
extern struct parser_LibraryParseResult parser_parse_one_function_library_from_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow_from_buf(struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len);
extern struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len);
extern void parser_parse_into_set_main_index(struct ast_Module * module, int32_t main_idx);
extern int32_t parser_diag_token_after_collect_imports(struct xlang_slice_uint8_t * source, struct ast_Module * module);
extern int32_t parser_diag_parse_one_after_collect_imports(struct xlang_slice_uint8_t * source, struct ast_Module * module, struct ast_ASTArena * arena);
extern int32_t parser_parse_one_function_ok_for_pipeline(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source);
extern int32_t parser_get_module_num_imports(struct ast_Module * module);
extern void parser_get_module_import_path(struct ast_Module * module, int32_t i, uint8_t * out);
extern int32_t parser_copy_module_import_path64(struct ast_Module * module, int32_t i, uint8_t * out);
extern int32_t parser_main(void);
extern uint8_t * calloc(size_t nmemb, size_t size);
extern void free(uint8_t * ptr);
extern int32_t std_fs_open(uint8_t * path);
extern ssize_t std_fs_read(int32_t fd, uint8_t * buf, size_t count);
extern int32_t std_fs_close(int32_t fd);
extern int32_t parser_parse_peek_function_name_buf_glue(struct lexer_Lexer lex, uint8_t * data, int32_t len, uint8_t * out);
int32_t parser_parse_peek_function_name_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, uint8_t * out) {
  return parser_parse_peek_function_name_buf_glue(lex, data, len, out);
  return 0;
}
extern struct xlang_slice_uint8_t parser_slice_from_buf(uint8_t * data, int32_t len);
extern void parser_diagnostic_parse_skip(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name);
extern int32_t parser_parse_strict_enabled(void);
extern void parser_skip_generic_angle_list_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_skip_generic_angle_list_count_into_glue(struct lexer_Lexer * out, int32_t * count, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
extern void parser_diagnostic_parse_commit_fail(int32_t byte_pos, int32_t num_funcs_so_far, int32_t name_len, uint8_t * name);
extern void parser_diagnostic_parse_func_generic(int32_t byte_pos, int32_t num_funcs_so_far, uint8_t * name, int32_t name_len, int32_t num_generic_params, int32_t is_main);
extern void parser_diagnostic_parse_commit_pre(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len, int32_t block_ref, uint8_t * pool, int32_t final_expr_ref);
extern void parser_diagnostic_parse_commit_post(struct ast_ASTArena * arena, uint8_t * name, int32_t name_len, int32_t block_ref, uint8_t * pool);
extern void pipeline_module_struct_layout_reset_slot(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern uint8_t pipeline_module_struct_layout_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_struct_layout_set_field(struct ast_Module * module, int32_t layout_idx, int32_t j, uint8_t * fname, int32_t fname_len, int32_t ftype_ref, int32_t foff);
extern int32_t pipeline_struct_layout_next_field_offset(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref);
extern int32_t pipeline_struct_layout_next_field_offset_ex(struct ast_Module * module, struct ast_ASTArena * arena, int32_t layout_idx, int32_t new_field_type_ref, int32_t field_align_req);
extern void pipeline_module_struct_layout_set_field_align(struct ast_Module * module, int32_t li, int32_t j, int32_t al);
extern int32_t pipeline_module_struct_layout_field_align_at(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_func_param_write(struct ast_Module * module, int32_t func_index, int32_t param_index, uint8_t * name_bytes, int32_t name_len, int32_t type_ref);
extern void pipeline_module_func_name_write(struct ast_Module * module, int32_t func_index, uint8_t * name_bytes, int32_t name_len);
extern void pipeline_arena_func_param_write(struct ast_ASTArena * arena, int32_t func_ref, int32_t param_index, uint8_t * name_bytes, int32_t name_len, int32_t type_ref);
extern void pipeline_arena_func_copy_slot_from_module(struct ast_ASTArena * arena, int32_t func_ref, struct ast_Module * module, int32_t fi);
extern void pipeline_module_reset_parse_counters_c(struct ast_Module * module);
void parser_pipeline_module_reset_parse_counters(struct ast_Module * module) {
  (void)(pipeline_module_reset_parse_counters_c(module));
}
extern size_t pipeline_sizeof_arena(void);
extern size_t pipeline_sizeof_onefunc_result(void);
extern void ast_pool_onefunc_reset(uint8_t * out);
extern void ast_pool_onefunc_release(uint8_t * out);
extern void driver_diagnostic_parser_onefunc_param_ref(uint8_t * func_name, int32_t func_name_len, uint8_t * param_name, int32_t param_name_len, int32_t stage, int32_t param_idx, int32_t type_ref);
extern void ast_pool_module_reset(struct ast_Module * module);
extern void ast_pool_arena_reset(struct ast_ASTArena * arena);
extern int32_t pipeline_module_func_alloc_slot(struct ast_Module * module);
extern void pipeline_module_func_ref_set(struct ast_Module * module, int32_t func_index, int32_t func_ref);
extern void pipeline_module_func_set_return_type(struct ast_Module * module, int32_t fi, int32_t type_ref);
extern void pipeline_module_func_set_body_ref(struct ast_Module * module, int32_t fi, int32_t body_ref);
extern void pipeline_module_func_set_body_expr_ref(struct ast_Module * module, int32_t fi, int32_t body_expr_ref);
extern void pipeline_module_func_set_is_extern(struct ast_Module * module, int32_t fi, int32_t is_extern);
extern void pipeline_module_func_set_is_async(struct ast_Module * module, int32_t fi, int32_t is_async);
extern void pipeline_module_func_set_is_export(struct ast_Module * module, int32_t fi, int32_t is_export);
extern void pipeline_module_func_set_is_used(struct ast_Module * module, int32_t fi, int32_t is_used);
extern void pipeline_module_func_set_is_naked(struct ast_Module * module, int32_t fi, int32_t is_naked);
extern void pipeline_module_func_set_is_entry(struct ast_Module * module, int32_t fi, int32_t is_entry);
extern void pipeline_module_func_set_is_no_mangle(struct ast_Module * module, int32_t fi, int32_t is_no_mangle);
extern void pipeline_module_func_set_is_interrupt(struct ast_Module * module, int32_t fi, int32_t is_interrupt);
extern void pipeline_module_func_set_is_variadic(struct ast_Module * module, int32_t fi, int32_t is_variadic);
extern int32_t pipeline_module_func_is_variadic_at(struct ast_Module * module, int32_t fi);
extern void pipeline_struct_layout_set_is_send(struct ast_Module * module, int32_t idx, int32_t is_send);
extern void pipeline_struct_layout_set_is_sync(struct ast_Module * module, int32_t idx, int32_t is_sync);
extern void pipeline_module_struct_layout_set_is_export(struct ast_Module * module, int32_t idx, int32_t is_export);
extern void pipeline_module_enum_set_is_export(struct ast_Module * module, int32_t idx, int32_t is_export);
extern void pipeline_module_top_level_let_set_is_export(struct ast_Module * module, int32_t idx, int32_t is_export);
extern void pipeline_module_func_set_num_params(struct ast_Module * module, int32_t fi, int32_t n);
extern void pipeline_module_func_set_num_generic_params(struct ast_Module * module, int32_t fi, int32_t n);
extern int32_t pipeline_block_append_const(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_let(struct ast_ASTArena * arena, int32_t br, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref);
extern int32_t pipeline_block_append_if(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_block_append_region(struct ast_ASTArena * arena, int32_t br, uint8_t * label, int32_t label_len, int32_t body_ref);
extern int32_t pipeline_block_append_unsafe(struct ast_ASTArena * arena, int32_t br, int32_t body_ref);
extern int32_t pipeline_block_append_with_arena(struct ast_ASTArena * arena, int32_t br, int32_t cap_ref, int32_t body_ref);
extern int32_t pipeline_block_append_expr_stmt(struct ast_ASTArena * arena, int32_t br, int32_t expr_ref);
extern int32_t pipeline_block_append_stmt_order(struct ast_ASTArena * arena, int32_t br, uint8_t kind, int32_t idx);
extern void pipeline_block_stmt_order_fix_prefix_lets(struct ast_ASTArena * arena, int32_t br, int32_t prefix_n);
extern void pipeline_block_with_arena_fixup_stmt_order(struct ast_ASTArena * arena, int32_t br);
extern void pipeline_block_fill_ifs_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_stmt_order_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_expr_stmts_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_onefunc_append_if(uint8_t * out, int32_t cond, int32_t then_ref, int32_t else_ref);
extern int32_t pipeline_onefunc_if_cond_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_if_then_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_if_else_body_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_if_stmts(uint8_t * out);
extern int32_t pipeline_onefunc_append_region(uint8_t * out, uint8_t * label, int32_t label_len, int32_t body_ref);
extern int32_t pipeline_onefunc_append_with_arena(uint8_t * out, int32_t cap_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_append_unsafe(uint8_t * out, int32_t body_ref);
extern int32_t pipeline_onefunc_num_regions(uint8_t * out);
extern void pipeline_block_fill_regions_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_block_append_defer(struct ast_ASTArena * arena, int32_t br, int32_t body_ref);
extern int32_t pipeline_block_defer_body_ref(struct ast_ASTArena * arena, int32_t br, int32_t di);
extern int32_t pipeline_onefunc_append_defer(uint8_t * out, int32_t body_ref);
extern int32_t pipeline_onefunc_num_defers(uint8_t * out);
extern void pipeline_block_fill_defers_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_onefunc_append_const_name(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val);
extern int32_t pipeline_onefunc_append_const(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t pipeline_onefunc_const_name_len(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_const_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_consts(uint8_t * out);
extern void pipeline_onefunc_const_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern int32_t pipeline_onefunc_append_let(uint8_t * out, uint8_t * name, int32_t name_len, int32_t init_val, int32_t init_ref, int32_t type_ref);
extern int32_t pipeline_onefunc_let_name_len(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_init_val(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_init_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_let_type_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_lets(uint8_t * out);
extern void pipeline_onefunc_let_name_copy64(uint8_t * out, int32_t i, uint8_t * dst);
extern void pipeline_onefunc_copy_sidecar(uint8_t * dst, uint8_t * src);
extern int32_t pipeline_onefunc_push_stmt_order(uint8_t * out, uint8_t kind, int32_t idx);
extern int32_t pipeline_onefunc_num_src_stmt_order(uint8_t * out);
extern uint8_t pipeline_onefunc_src_stmt_kind(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_src_stmt_idx(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_push_body_expr_stmt(uint8_t * out, int32_t expr_ref);
extern int32_t pipeline_onefunc_body_expr_stmt_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_num_body_expr_stmts(uint8_t * out);
extern int32_t pipeline_onefunc_append_param(uint8_t * out, uint8_t * name, int32_t name_len, int32_t type_ref);
extern void pipeline_onefunc_set_param_type_ref(uint8_t * out, int32_t i, int32_t type_ref);
extern int32_t pipeline_onefunc_param_name_len(uint8_t * out, int32_t i);
extern uint8_t pipeline_onefunc_param_name_byte_at(uint8_t * out, int32_t i, int32_t off);
extern void pipeline_onefunc_param_name_copy32(uint8_t * out, int32_t i, uint8_t * dst);
extern int32_t pipeline_onefunc_param_type_ref(uint8_t * out, int32_t i);
extern int32_t pipeline_onefunc_call_arg_val_at(uint8_t * out, int32_t i);
extern void pipeline_onefunc_reset_call_args(uint8_t * out);
extern int32_t pipeline_block_append_while(struct ast_ASTArena * arena, int32_t br, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_block_append_for(struct ast_ASTArena * arena, int32_t br, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern void pipeline_block_fill_whiles_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern void pipeline_block_fill_fors_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_onefunc_append_while(uint8_t * out, int32_t cond_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_num_whiles(uint8_t * out);
extern int32_t pipeline_onefunc_append_for(uint8_t * out, int32_t init_ref, int32_t cond_ref, int32_t step_ref, int32_t body_ref);
extern int32_t pipeline_onefunc_num_fors(uint8_t * out);
extern void pipeline_parser_set_match_module(struct ast_Module * m);
extern struct ast_Module * pipeline_parser_get_match_module(void);
extern int32_t pipeline_module_enum_variant_tag_for_names(struct ast_Module * m, uint8_t * enum_name, int32_t enum_len, uint8_t * variant_name, int32_t variant_len);
extern int32_t pipeline_expr_append_match_arm(struct ast_ASTArena * arena, int32_t expr_ref, int32_t result_ref, int32_t is_wildcard, int32_t lit_val, int32_t is_enum_variant, int32_t variant_index);
extern int32_t pipeline_expr_append_array_lit_elem(struct ast_ASTArena * arena, int32_t expr_ref, int32_t elem_ref);
extern int32_t pipeline_expr_append_call_arg(struct ast_ASTArena * arena, int32_t expr_ref, int32_t arg_ref);
extern void lexer_next_buf_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
extern int32_t ast_block_expr_stmt_ref(struct ast_ASTArena * arena, int32_t block_ref, int32_t ei);
extern int32_t pipeline_block_append_labeled(struct ast_ASTArena * arena, int32_t br, int32_t label_len, int32_t is_goto, int32_t goto_target_len, int32_t return_expr_ref);
extern void pipeline_block_labeled_set_names(struct ast_ASTArena * arena, int32_t br, int32_t li, uint8_t * label, int32_t label_len, uint8_t * goto_target, int32_t goto_target_len);
/* wave379: OneFunc labeled/goto pool (stmt_order kind=7). PLATFORM: SHARED */
extern int32_t pipeline_onefunc_append_labeled(uint8_t * out, uint8_t * label, int32_t label_len, int32_t is_goto, uint8_t * goto_target, int32_t goto_target_len, int32_t return_expr_ref);
extern int32_t pipeline_onefunc_num_labeleds(uint8_t * out);
extern void pipeline_block_fill_labeled_from_onefunc(struct ast_ASTArena * arena, int32_t br, uint8_t * out, int32_t count);
extern int32_t pipeline_module_struct_layout_alloc(struct ast_Module * module);
extern int32_t pipeline_module_struct_layout_name_len(struct ast_Module * module, int32_t idx);
extern int32_t pipeline_module_struct_layout_num_fields(struct ast_Module * module, int32_t idx);
extern void pipeline_module_struct_layout_set_num_fields(struct ast_Module * module, int32_t idx, int32_t nf);
extern int32_t pipeline_module_struct_layout_field_name_len(struct ast_Module * module, int32_t li, int32_t j);
extern int32_t pipeline_module_struct_layout_field_type_ref(struct ast_Module * module, int32_t li, int32_t j);
extern void pipeline_module_struct_layout_set_allow_padding(struct ast_Module * module, int32_t idx, int32_t v);
extern void pipeline_module_struct_layout_set_soa(struct ast_Module * module, int32_t idx, int32_t v);
extern int32_t pipeline_module_import_alloc(struct ast_Module * module);
extern void pipeline_module_import_set_path(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_import_set_kind(struct ast_Module * module, int32_t idx, int32_t kind);
extern void pipeline_module_import_set_binding_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_import_set_select_count(struct ast_Module * module, int32_t idx, int32_t n);
extern int32_t pipeline_module_import_append_select_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern void pipeline_module_import_path_copy(struct ast_Module * module, int32_t idx, uint8_t * dst, int32_t dst_cap);
extern int32_t pipeline_module_enum_alloc(struct ast_Module * module);
extern int32_t pipeline_module_enum_name_len(struct ast_Module * module, int32_t idx);
extern uint8_t pipeline_module_enum_name_byte_at(struct ast_Module * module, int32_t idx, int32_t off);
extern void pipeline_module_enum_set_name(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_module_enum_append_variant(struct ast_Module * module, int32_t idx, uint8_t * bytes, int32_t len);
extern int32_t pipeline_type_ensure_by_kind_ord(struct ast_ASTArena * arena, int32_t kind_ord);
extern int32_t pipeline_module_top_level_let_alloc(struct ast_Module * module);
extern void pipeline_module_top_level_let_set(struct ast_Module * module, int32_t idx, uint8_t * name, int32_t name_len, int32_t type_ref, int32_t init_ref, int32_t is_const);
uint8_t * parser_onefunc_result_pool_ptr(struct parser_OneFuncResult * res) {
  return ((uint8_t *)(res));
}
extern void parser_lex_copy_from_collect_imports(struct lexer_Lexer * out, struct parser_CollectImportsResult res);
void parser_copy_lex_from_import_into(struct lexer_Lexer * out, struct parser_CollectImportsResult res) {
  (void)(parser_lex_copy_from_collect_imports(out, res));
}
extern void parser_lex_from_lexer_result_val_into(struct lexer_Lexer * out, struct lexer_LexerResult r);
extern void parser_lex_from_next_into_glue(struct lexer_Lexer * out, struct lexer_LexerResult r);
void parser_lex_from_next_into(struct lexer_Lexer * out, struct lexer_LexerResult r) {
  (void)(parser_lex_from_next_into_glue(out, r));
}
extern void parser_lex_from_lexer_result_ptr_into(struct lexer_Lexer * out, struct lexer_LexerResult * r);
extern void parser_lex_from_result_ptr_into_glue(struct lexer_Lexer * out_lex, struct lexer_LexerResult * r);
void parser_lex_from_result_ptr_into(struct lexer_Lexer * out_lex, struct lexer_LexerResult * r) {
  (void)(parser_lex_from_result_ptr_into_glue(out_lex, r));
}
void parser_lexer_copy_into(struct lexer_Lexer * out_lex, struct lexer_Lexer src_lex) {
  (void)(((out_lex->pos) = (src_lex.pos)));
  (void)(((out_lex->line) = (src_lex.line)));
  (void)(((out_lex->col) = (src_lex.col)));
}
void parser_lexer_copy_from_parse_expr_result_into(struct lexer_Lexer * out_lex, struct parser_ParseExprResult * res) {
  (void)(((out_lex->pos) = ((res->next_lex).pos)));
  (void)(((out_lex->line) = ((res->next_lex).line)));
  (void)(((out_lex->col) = ((res->next_lex).col)));
}
void parser_parse_expr_result_reset(struct parser_ParseExprResult * out_res, struct lexer_Lexer next_lex) {
  (void)(((out_res->ok) = 0));
  (void)(((out_res->expr_ref) = 0));
  (void)((((out_res->next_lex).pos) = (next_lex.pos)));
  (void)((((out_res->next_lex).line) = (next_lex.line)));
  (void)((((out_res->next_lex).col) = (next_lex.col)));
}
void parser_rewind_lex_for_following_stmt_into(struct lexer_Lexer * out_lex, struct lexer_Lexer lex_in, struct lexer_LexerResult r) {
  {
    struct lexer_Lexer rewound = parser_rewind_lex_for_following_stmt(lex_in, r);
    (void)(parser_lexer_copy_into(out_lex, rewound));
  }
}
extern void parser_lex_from_onefunc_result_ptr_into(struct lexer_Lexer * out, struct parser_OneFuncResult * res);
extern void parser_lex_from_onefunc_next_into_glue(struct lexer_Lexer * out, struct parser_OneFuncResult * res);
void parser_lex_from_onefunc_next_into(struct lexer_Lexer * out, struct parser_OneFuncResult * res) {
  (void)(parser_lex_from_onefunc_next_into_glue(out, res));
}
size_t parser_lexer_pos_before_run(size_t end_pos, int32_t run_len) {
  {
    int32_t rl = run_len;
    size_t start = (end_pos - ((size_t)(rl)));
    return start;
  }
}
int32_t parser_lexer_token_run_len(enum token_TokenKind kind) {
  {
    if ((kind ==11)) {
      return 6;
    }
    if ((kind ==1)) {
      return 8;
    }
    if ((kind ==3)) {
      return 5;
    }
    if ((kind ==6)) {
      return 5;
    }
    if ((kind ==76)) {
      return 5;
    }
    if ((kind ==19)) {
      return 6;
    }
    if ((kind ==53)) {
      return 6;
    }
    if ((kind ==54)) {
      return 6;
    }
    if ((kind ==131)) {
      return 6;
    }
    int32_t ko = ((int32_t)(kind));
    if ((ko ==29)) {
      return 5;
    }
    if ((kind ==2)) {
      return 3;
    }
    if ((kind ==4)) {
      return 2;
    }
    if ((kind ==8)) {
      return 3;
    }
    if ((kind ==5)) {
      return 4;
    }
    if ((kind ==75)) {
      return 4;
    }
    if ((kind ==47)) {
      return 4;
    }
    if ((kind ==18)) {
      return 5;
    }
    return 1;
  }
}
extern struct lexer_Lexer parser_lex_at_token_from_result_glue(struct lexer_LexerResult r);
struct lexer_Lexer parser_lex_at_token_from_result(struct lexer_LexerResult r) {
  return parser_lex_at_token_from_result_glue(r);
}
extern struct lexer_Lexer parser_parser_rewind_lex_for_following_stmt_glue(struct lexer_Lexer lex_in, struct lexer_LexerResult r);
extern void parser_asm_parse_block_return_end_tail_glue(struct lexer_LexerResult * r, struct lexer_Lexer * lex_cur, struct xlang_slice_uint8_t * source, int * stmt_tok_ready, int32_t * block_break);
struct lexer_Lexer parser_rewind_lex_for_following_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r) {
  return parser_parser_rewind_lex_for_following_stmt_glue(lex_in, r);
}
struct lexer_Lexer parser_realign_lex_after_compound_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r_in, struct xlang_slice_uint8_t * source) {
  {
    struct lexer_Lexer lex_out = parser_rewind_lex_for_following_stmt(lex_in, r_in);
    (void)((lex_out = parser_rewind_lex_for_lparen_control_stmt(lex_out, r_in, source)));
    return lex_out;
  }
}
/* Forward decl: used by lparen rewind probe before the later extern block. */
extern void lexer_invalid_type_suffix_reset(void);

/**
 * wave1218: absolute (line, col) for byte pos by scanning source[0..pos).
 * PLATFORM: SHARED — seed pin twin of parser_gen.c.
 */
static void parser_lexer_line_col_at_pos(struct xlang_slice_uint8_t *source, size_t pos,
                                        int32_t *out_line, int32_t *out_col) {
  int32_t line = 1;
  int32_t col = 1;
  size_t i = 0;
  size_t lim;
  if (!out_line || !out_col)
    return;
  if (!source || !source->data) {
    *out_line = 1;
    *out_col = 1;
    return;
  }
  lim = source->length;
  if (pos < lim)
    lim = pos;
  for (i = 0; i < lim; i++) {
    if (source->data[i] == 10) {
      line = line + 1;
      col = 1;
    } else {
      col = col + 1;
    }
  }
  *out_line = line;
  *out_col = col;
}

/* Anti-loop: same re-sync target accepted >32 times → refuse (twin of parser.x). */
static size_t g_lparen_ctrl_last_pos = 0;
static int32_t g_lparen_ctrl_hits = 0;

struct lexer_Lexer parser_rewind_lex_for_lparen_control_stmt(struct lexer_Lexer lex_in, struct lexer_LexerResult r_in, struct xlang_slice_uint8_t * source) {
  /* PLATFORM: SHARED — seed pin twin of parser.x / parser_gen.linux.x86_64.c.
   * Only re-sync when if/while/for is the *immediate* predecessor of `(`
   * (whitespace only between). Prior 128-byte scan false-matched outer `if`
   * for nested paren exprs inside conditions:
   *   if (f(unsafe { (1) }) != 0) { ... }
   * → infinite parse_if_stmt recursion / stack overflow.
   * Safety: same new_pos >32 times → return lex_in (no hang / unkillable spinner). */
  if ((((r_in.tok).kind) ==82)) {
    struct lexer_Lexer lp_base = parser_lex_at_token_from_result(r_in);
    size_t lp_pos = (lp_base.pos);
    size_t end = lp_pos;
    while (end > 0) {
      uint8_t c = (source)->data[end - 1];
      if (c == 32 || c == 9 || c == 10 || c == 13) {
        end = end - 1;
        continue;
      }
      break;
    }
    if (end == 0) {
      return lex_in;
    }
    int32_t kw_len = 0;
    if (end >= 5
        && (source)->data[end - 5] == 119 && (source)->data[end - 4] == 104
        && (source)->data[end - 3] == 105 && (source)->data[end - 2] == 108
        && (source)->data[end - 1] == 101) {
      kw_len = 5; /* while */
    } else if (end >= 3
        && (source)->data[end - 3] == 102 && (source)->data[end - 2] == 111
        && (source)->data[end - 1] == 114) {
      kw_len = 3; /* for */
    } else if (end >= 2
        && (source)->data[end - 2] == 105 && (source)->data[end - 1] == 102) {
      kw_len = 2; /* if */
    }
    if (kw_len == 0) {
      return lex_in;
    }
    size_t new_pos = end - (size_t)kw_len;
    if (new_pos > 0) {
      uint8_t b = (source)->data[new_pos - 1];
      if ((b >= 97 && b <= 122) || (b >= 65 && b <= 90) || (b >= 48 && b <= 57) || b == 95) {
        return lex_in;
      }
    }
    if (new_pos == g_lparen_ctrl_last_pos) {
      g_lparen_ctrl_hits = g_lparen_ctrl_hits + 1;
      if (g_lparen_ctrl_hits > 32) {
        return lex_in;
      }
    } else {
      g_lparen_ctrl_last_pos = new_pos;
      g_lparen_ctrl_hits = 1;
    }
    int32_t rew_line = 1;
    int32_t rew_col = 1;
    parser_lexer_line_col_at_pos(source, new_pos, &rew_line, &rew_col);
    struct lexer_Lexer lex_lp = (struct lexer_Lexer){ .pos = new_pos, .line = rew_line, .col = rew_col };
    struct lexer_LexerResult r_lp = (struct lexer_LexerResult){ .next_lex = lex_lp, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    (void)(lexer_next_into(&(r_lp), lex_lp, source));
    lexer_invalid_type_suffix_reset();
    if ((((((r_lp.tok).kind) ==4) || (((r_lp.tok).kind) ==6)) || (((r_lp.tok).kind) ==8))) {
      return parser_rewind_lex_for_following_stmt(lex_in, r_lp);
    }
  }
  return lex_in;
}
int parser_match_kw_immediately_before(struct xlang_slice_uint8_t * source, size_t ident_start) {
  {
    if ((ident_start < 6)) {
      return 0;
    }
    size_t p = (ident_start - 6);
    return (((((((source)->data[p] ==109) && ((source)->data[(p + 1)] ==97)) && ((source)->data[(p + 2)] ==116)) && ((source)->data[(p + 3)] ==99)) && ((source)->data[(p + 4)] ==104)) && ((source)->data[(p + 5)] ==32));
  }
}
int parser_return_kw_immediately_before(struct xlang_slice_uint8_t * source, size_t ident_start) {
  {
    if ((ident_start < 7)) {
      return 0;
    }
    size_t p = (ident_start - 7);
    if ((((((((source)->data[p] !=114) || ((source)->data[(p + 1)] !=101)) || ((source)->data[(p + 2)] !=116)) || ((source)->data[(p + 3)] !=117)) || ((source)->data[(p + 4)] !=114)) || ((source)->data[(p + 5)] !=110))) {
      return 0;
    }
    uint8_t sep = (source)->data[(p + 6)];
    return ((((sep ==32) || (sep ==9)) || (sep ==10)) || (sep ==13));
  }
}
int parser_match_kw_immediately_before_buf(uint8_t * data, int32_t len, size_t ident_start) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_match_kw_immediately_before(&(slice), ident_start);
  }
  return 0;
}
extern int32_t parser_advance_past_stmt_semicolon_into_glue(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
int32_t parser_advance_past_stmt_semicolon_into(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_advance_past_stmt_semicolon_into_glue(r_out, lex, source);
  return 0;
}
int32_t parser_advance_past_stmt_semicolon_into_buf(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_advance_past_stmt_semicolon_into(r_out, lex, &(slice));
  }
  return 0;
}
extern int32_t parser_advance_past_cond_rparen_into_glue(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
int32_t parser_advance_past_cond_rparen_into(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_advance_past_cond_rparen_into_glue(r_out, lex, source);
  return 0;
}
int32_t parser_advance_past_cond_rparen_into_buf(struct lexer_LexerResult * r_out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_advance_past_cond_rparen_into(r_out, lex, &(slice));
  }
  return 0;
}
void parser_onefunc_result_layout_prime(void) {
  {
    uint8_t z64[128] = {};
    struct parser_OneFuncResult _prime = (struct parser_OneFuncResult){ .ok = 0, .next_lex = lexer_init(), .name = {z64[0], z64[1], z64[2], z64[3], z64[4], z64[5], z64[6], z64[7], z64[8], z64[9], z64[10], z64[11], z64[12], z64[13], z64[14], z64[15], z64[16], z64[17], z64[18], z64[19], z64[20], z64[21], z64[22], z64[23], z64[24], z64[25], z64[26], z64[27], z64[28], z64[29], z64[30], z64[31], z64[32], z64[33], z64[34], z64[35], z64[36], z64[37], z64[38], z64[39], z64[40], z64[41], z64[42], z64[43], z64[44], z64[45], z64[46], z64[47], z64[48], z64[49], z64[50], z64[51], z64[52], z64[53], z64[54], z64[55], z64[56], z64[57], z64[58], z64[59], z64[60], z64[61], z64[62], z64[63]}, .name_len = 0, .num_params = 0 };
    (void)(((_prime.name_len) = 0));
  }
}
void parser_set_onefunc_fail(struct parser_OneFuncResult * out, struct lexer_Lexer next_lex) {
  (void)(parser_diagnostic_parse_skip(((int32_t)((next_lex.pos))), -(1), (out->name_len), &(((out->name))[0])));
  (void)(((out->ok) = 0));
  (void)(((out->next_lex) = next_lex));
}
int parser_onefunc_finish_after_return_lex(struct parser_OneFuncResult * out, struct parser_OneFuncResult * impl_snap, struct xlang_slice_uint8_t * source, struct lexer_Lexer lex_after_expr, uint8_t * func_name, int32_t func_name_len, int32_t return_expr_ref) {
  {
    struct lexer_LexerResult r_tail = (struct lexer_LexerResult){ .next_lex = lex_after_expr, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    struct lexer_Lexer lex_tail = lex_after_expr;
    if ((parser_advance_past_stmt_semicolon_into(&(r_tail), lex_after_expr, source) ==0)) {
      return 0;
    }
    if ((((r_tail.tok).kind) ==95)) {
      (void)(parser_lex_from_result_ptr_into(&(lex_tail), &(r_tail)));
      (void)(lexer_next_into(&(r_tail), lex_tail, source));
    }
    if ((((r_tail.tok).kind) !=85)) {
      return 0;
    }
    (void)(parser_lex_from_next_into(&(lex_tail), r_tail));
    (void)(parser_onefunc_finish_impl_to_out(out, impl_snap, lex_tail, func_name, func_name_len, return_expr_ref));
    return 1;
  }
}
void parser_onefunc_result_layout_prime_b(void) {
  {
    struct parser_OneFuncResult _q2 = (struct parser_OneFuncResult){ .num_consts = 0, .num_lets = 0 };
    (void)(((_q2.num_consts) = 0));
  }
}
void parser_onefunc_result_layout_prime_c(void) {
  {
    struct parser_OneFuncResult _q3 = (struct parser_OneFuncResult){ .has_if_expr = 0, .if_cond_true = 0, .if_then_val = 0, .if_else_val = 0, .if_cond_expr_ref = 0, .has_mul = 0, .mul_right_val = 0 };
    (void)(((_q3.if_cond_expr_ref) = 0));
  }
}
void parser_onefunc_result_layout_prime_d(void) {
  {
    uint8_t ccn[128] = {};
    struct parser_OneFuncResult _q4 = (struct parser_OneFuncResult){ .has_binop = 0, .binop_right_val = 0, .binop_left_param_idx = -(1), .binop_right_param_idx = -(1), .has_unary_neg = 0, .return_val = 0, .has_call_expr = 0, .call_callee_name = {ccn[0], ccn[1], ccn[2], ccn[3], ccn[4], ccn[5], ccn[6], ccn[7], ccn[8], ccn[9], ccn[10], ccn[11], ccn[12], ccn[13], ccn[14], ccn[15], ccn[16], ccn[17], ccn[18], ccn[19], ccn[20], ccn[21], ccn[22], ccn[23], ccn[24], ccn[25], ccn[26], ccn[27], ccn[28], ccn[29], ccn[30], ccn[31], ccn[32], ccn[33], ccn[34], ccn[35], ccn[36], ccn[37], ccn[38], ccn[39], ccn[40], ccn[41], ccn[42], ccn[43], ccn[44], ccn[45], ccn[46], ccn[47], ccn[48], ccn[49], ccn[50], ccn[51], ccn[52], ccn[53], ccn[54], ccn[55], ccn[56], ccn[57], ccn[58], ccn[59], ccn[60], ccn[61], ccn[62], ccn[63]} };
    (void)(((_q4.binop_left_param_idx) = -(1)));
  }
}
void parser_onefunc_result_layout_prime_d_b(void) {
  {
    uint8_t rvn[128] = {};
    struct parser_OneFuncResult _q4b = (struct parser_OneFuncResult){ .call_callee_len = 0, .return_var_name = {rvn[0], rvn[1], rvn[2], rvn[3], rvn[4], rvn[5], rvn[6], rvn[7], rvn[8], rvn[9], rvn[10], rvn[11], rvn[12], rvn[13], rvn[14], rvn[15], rvn[16], rvn[17], rvn[18], rvn[19], rvn[20], rvn[21], rvn[22], rvn[23], rvn[24], rvn[25], rvn[26], rvn[27], rvn[28], rvn[29], rvn[30], rvn[31], rvn[32], rvn[33], rvn[34], rvn[35], rvn[36], rvn[37], rvn[38], rvn[39], rvn[40], rvn[41], rvn[42], rvn[43], rvn[44], rvn[45], rvn[46], rvn[47], rvn[48], rvn[49], rvn[50], rvn[51], rvn[52], rvn[53], rvn[54], rvn[55], rvn[56], rvn[57], rvn[58], rvn[59], rvn[60], rvn[61], rvn[62], rvn[63]}, .return_var_name_len = 0, .return_expr_ref = 0, .call_num_args = 0, .num_loops = 0 };
    (void)(((_q4b.call_num_args) = 0));
  }
}
void parser_onefunc_result_layout_prime_e(void) {
  {
    struct parser_OneFuncResult _q5 = (struct parser_OneFuncResult){ .num_for_loops = 0, .num_if_stmts = 0 };
    (void)(((_q5.num_if_stmts) = 0));
  }
}
void parser_onefunc_result_layout_prime_f(void) {
  {
    struct parser_OneFuncResult _q6 = (struct parser_OneFuncResult){ .num_src_stmt_order = 0, .num_src_body_expr_stmts = 0, .func_return_type_ref = 0, .is_variadic = 0 };
    (void)(((_q6.func_return_type_ref) = 0));
    (void)(((_q6.is_variadic) = 0));
  }
}
void parser_copy_onefunc_into(struct parser_OneFuncResult * dst, struct parser_OneFuncResult * src) {
  {
    int32_t preserved_func_ret_ty = (dst->func_return_type_ref);
    (void)(pipeline_onefunc_copy_sidecar(parser_onefunc_result_pool_ptr(dst), parser_onefunc_result_pool_ptr(src)));
    (void)(((dst->ok) = (src->ok)));
    (void)(((dst->next_lex) = (src->next_lex)));
    (void)(((dst->name_len) = (src->name_len)));
    int32_t ni = 0;
    while ((ni < 128)) {
      if ((ni < (src->name_len))) {
        (void)((((dst->name))[ni] = ((src->name))[ni]));
      }
      (void)((ni = (ni + 1)));
    }
    (void)(((dst->num_params) = (src->num_params)));
    (void)(((dst->num_generic_params) = (src->num_generic_params)));
    (void)(((dst->num_consts) = pipeline_onefunc_num_consts(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->has_if_expr) = (src->has_if_expr)));
    (void)(((dst->if_cond_true) = (src->if_cond_true)));
    (void)(((dst->if_then_val) = (src->if_then_val)));
    (void)(((dst->if_else_val) = (src->if_else_val)));
    (void)(((dst->if_cond_expr_ref) = (src->if_cond_expr_ref)));
    (void)(((dst->has_mul) = (src->has_mul)));
    (void)(((dst->mul_right_val) = (src->mul_right_val)));
    (void)(((dst->has_binop) = (src->has_binop)));
    (void)(((dst->binop_right_val) = (src->binop_right_val)));
    (void)(((dst->binop_left_param_idx) = (src->binop_left_param_idx)));
    (void)(((dst->binop_right_param_idx) = (src->binop_right_param_idx)));
    (void)(((dst->has_unary_neg) = (src->has_unary_neg)));
    (void)(((dst->return_val) = (src->return_val)));
    (void)(((dst->return_var_name_len) = (src->return_var_name_len)));
    int32_t rvni = 0;
    while ((rvni < 128)) {
      (void)((((dst->return_var_name))[rvni] = ((src->return_var_name))[rvni]));
      (void)((rvni = (rvni + 1)));
    }
    (void)(((dst->return_expr_ref) = (src->return_expr_ref)));
    (void)(((dst->has_final_expr) = (src->has_final_expr)));
    (void)(((dst->has_explicit_return_kw) = (src->has_explicit_return_kw)));
    (void)(((dst->has_call_expr) = (src->has_call_expr)));
    (void)(((dst->call_callee_len) = (src->call_callee_len)));
    int32_t cci = 0;
    while ((cci < 128)) {
      (void)((((dst->call_callee_name))[cci] = ((src->call_callee_name))[cci]));
      (void)((cci = (cci + 1)));
    }
    (void)(((dst->call_num_args) = (src->call_num_args)));
    (void)(((dst->num_loops) = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->num_for_loops) = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->num_if_stmts) = pipeline_onefunc_num_if_stmts(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->num_src_stmt_order) = pipeline_onefunc_num_src_stmt_order(parser_onefunc_result_pool_ptr(dst))));
    (void)(((dst->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(dst))));
    if (((src->func_return_type_ref) !=0)) {
      (void)(((dst->func_return_type_ref) = (src->func_return_type_ref)));
    } else {
      (void)(((dst->func_return_type_ref) = preserved_func_ret_ty));
    }
    /* Cap 10.7.1: copy variadic flag (≡ parser.x). */
    (void)(((dst->is_variadic) = (src->is_variadic)));
  }
}
struct parser_OneFuncResult parser_onefunc_scratch_empty(void) {
  {
    uint8_t z64[128] = {};
    return (struct parser_OneFuncResult){ .ok = 0, .next_lex = lexer_init(), .name = {z64[0], z64[1], z64[2], z64[3], z64[4], z64[5], z64[6], z64[7], z64[8], z64[9], z64[10], z64[11], z64[12], z64[13], z64[14], z64[15], z64[16], z64[17], z64[18], z64[19], z64[20], z64[21], z64[22], z64[23], z64[24], z64[25], z64[26], z64[27], z64[28], z64[29], z64[30], z64[31], z64[32], z64[33], z64[34], z64[35], z64[36], z64[37], z64[38], z64[39], z64[40], z64[41], z64[42], z64[43], z64[44], z64[45], z64[46], z64[47], z64[48], z64[49], z64[50], z64[51], z64[52], z64[53], z64[54], z64[55], z64[56], z64[57], z64[58], z64[59], z64[60], z64[61], z64[62], z64[63]}, .name_len = 0, .num_params = 0 };
  }
}
void parser_onefunc_merge_pool_out_to_snap(struct parser_OneFuncResult * snap, struct parser_OneFuncResult * out) {
  (void)(pipeline_onefunc_copy_sidecar(parser_onefunc_result_pool_ptr(snap), parser_onefunc_result_pool_ptr(out)));
  (void)(((snap->num_params) = (out->num_params)));
  (void)(((snap->num_generic_params) = (out->num_generic_params)));
  if (((out->func_return_type_ref) !=0)) {
    (void)(((snap->func_return_type_ref) = (out->func_return_type_ref)));
  }
  /* Cap 10.7.1: keep variadic across pool merge (≡ parser.x). */
  (void)(((snap->is_variadic) = (out->is_variadic)));
  (void)(((snap->num_consts) = pipeline_onefunc_num_consts(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_if_stmts) = pipeline_onefunc_num_if_stmts(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_src_stmt_order) = pipeline_onefunc_num_src_stmt_order(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_loops) = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(snap))));
  (void)(((snap->num_for_loops) = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(snap))));
}
void parser_onefunc_finish_impl_to_out(struct parser_OneFuncResult * out, struct parser_OneFuncResult * snap, struct lexer_Lexer lex, uint8_t * name, int32_t name_len, int32_t ret_expr_storage) {
  {
    (void)(parser_onefunc_merge_pool_out_to_snap(snap, out));
    (void)(((snap->return_expr_ref) = ret_expr_storage));
    (void)(((snap->ok) = 1));
    (void)(((snap->next_lex) = lex));
    (void)(((snap->name_len) = name_len));
    int32_t ni = 0;
    while ((ni < 128)) {
      (void)((((snap->name))[ni] = (name)[ni]));
      (void)((ni = (ni + 1)));
    }
    (void)(parser_copy_onefunc_into(out, snap));
  }
}
void parser_onefunc_res_wire_dummy_head(struct parser_OneFuncResult * res, struct lexer_Lexer lex, uint8_t * name64) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .ok = 0, .next_lex = lex, .name = {name64[0], name64[1], name64[2], name64[3], name64[4], name64[5], name64[6], name64[7], name64[8], name64[9], name64[10], name64[11], name64[12], name64[13], name64[14], name64[15], name64[16], name64[17], name64[18], name64[19], name64[20], name64[21], name64[22], name64[23], name64[24], name64[25], name64[26], name64[27], name64[28], name64[29], name64[30], name64[31], name64[32], name64[33], name64[34], name64[35], name64[36], name64[37], name64[38], name64[39], name64[40], name64[41], name64[42], name64[43], name64[44], name64[45], name64[46], name64[47], name64[48], name64[49], name64[50], name64[51], name64[52], name64[53], name64[54], name64[55], name64[56], name64[57], name64[58], name64[59], name64[60], name64[61], name64[62], name64[63]}, .name_len = 0, .num_params = 0 };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
void parser_onefunc_res_wire_dummy_const_let(struct parser_OneFuncResult * res) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .num_consts = 0, .num_lets = 0 };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
void parser_onefunc_res_wire_dummy_if_mul(struct parser_OneFuncResult * res) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .has_if_expr = 0, .if_cond_true = 0, .if_then_val = 0, .if_else_val = 0, .if_cond_expr_ref = 0, .has_mul = 0, .mul_right_val = 0 };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
void parser_onefunc_res_wire_dummy_call_binop(struct parser_OneFuncResult * res, uint8_t * name64) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .has_binop = 0, .binop_right_val = 0, .binop_left_param_idx = -(1), .binop_right_param_idx = -(1), .has_unary_neg = 0, .return_val = 0, .has_call_expr = 0, .call_callee_name = {name64[0], name64[1], name64[2], name64[3], name64[4], name64[5], name64[6], name64[7], name64[8], name64[9], name64[10], name64[11], name64[12], name64[13], name64[14], name64[15], name64[16], name64[17], name64[18], name64[19], name64[20], name64[21], name64[22], name64[23], name64[24], name64[25], name64[26], name64[27], name64[28], name64[29], name64[30], name64[31], name64[32], name64[33], name64[34], name64[35], name64[36], name64[37], name64[38], name64[39], name64[40], name64[41], name64[42], name64[43], name64[44], name64[45], name64[46], name64[47], name64[48], name64[49], name64[50], name64[51], name64[52], name64[53], name64[54], name64[55], name64[56], name64[57], name64[58], name64[59], name64[60], name64[61], name64[62], name64[63]} };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
void parser_onefunc_res_wire_dummy_loop_call(struct parser_OneFuncResult * res) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .call_callee_len = 0, .return_var_name_len = 0, .return_expr_ref = 0, .call_num_args = 0, .num_loops = 0 };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
void parser_onefunc_res_wire_dummy_for_if(struct parser_OneFuncResult * res) {
  {
    struct parser_OneFuncResult _w = (struct parser_OneFuncResult){ .num_for_loops = 0, .num_if_stmts = 0 };
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(_w))));
    (void)(parser_copy_onefunc_into(res, &(_w)));
  }
}
struct parser_OneFuncResult parser_onefunc_alloc_wired_for_parse(struct lexer_Lexer lex) {
  {
    uint8_t dummy_name[128] = {};
    struct parser_OneFuncResult res = parser_onefunc_scratch_empty();
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(res))));
    (void)(parser_onefunc_res_wire_dummy_head(&(res), lex, dummy_name));
    (void)(parser_onefunc_res_wire_dummy_const_let(&(res)));
    (void)(parser_onefunc_res_wire_dummy_if_mul(&(res)));
    (void)(parser_onefunc_res_wire_dummy_call_binop(&(res), dummy_name));
    (void)(parser_onefunc_res_wire_dummy_loop_call(&(res)));
    (void)(parser_onefunc_res_wire_dummy_for_if(&(res)));
    return res;
  }
}
void parser_onefunc_snap_set_return_path(struct parser_OneFuncResult * snap, int has_call, uint8_t * ret_var, int32_t ret_var_len, int32_t ret_expr_ref) {
  {
    (void)(((snap->has_call_expr) = has_call));
    (void)(((snap->return_var_name_len) = ret_var_len));
    (void)(((snap->return_expr_ref) = ret_expr_ref));
    (void)(((snap->has_explicit_return_kw) = 1));
    int32_t rvni = 0;
    while ((rvni < 128)) {
      (void)((((snap->return_var_name))[rvni] = (ret_var)[rvni]));
      (void)((rvni = (rvni + 1)));
    }
  }
}
void parser_onefunc_push_src_stmt(struct parser_OneFuncResult * out, uint8_t kind, int32_t idx) {
  {
    int32_t _so = pipeline_onefunc_push_stmt_order(parser_onefunc_result_pool_ptr(out), kind, idx);
    if ((_so >=0)) {
      (void)(((out->num_src_stmt_order) = pipeline_onefunc_num_src_stmt_order(parser_onefunc_result_pool_ptr(out))));
    }
  }
}
extern void parser_expr_set_common_zeros_glue(struct ast_Expr * e);
void parser_expr_set_common_zeros(struct ast_Expr * e) {
  (void)(parser_expr_set_common_zeros_glue(e));
}
int32_t parser_alloc_true_bool_lit(struct ast_ASTArena * arena) {
  {
    int32_t ref = ast_ast_arena_expr_alloc(arena);
    if ((ref ==0)) {
      return 0;
    }
    struct ast_Expr e = ast_ast_arena_expr_get(arena, ref);
    (void)(((e.kind) = 2));
    (void)(((e.int_val) = 1));
    (void)(((e.line) = 0));
    (void)(((e.col) = 0));
    (void)(parser_expr_set_common_zeros(&(e)));
    (void)(ast_ast_arena_expr_set(arena, ref, e));
    return ref;
  }
}
int32_t parser_alloc_float_lit(struct ast_ASTArena * arena, double fval) {
  {
    int32_t ref = ast_ast_arena_expr_alloc(arena);
    if ((ref ==0)) {
      return 0;
    }
    struct ast_Expr e = ast_ast_arena_expr_get(arena, ref);
    (void)(((e.kind) = 1));
    (void)(((e.float_val) = fval));
    (void)(((e.line) = 0));
    (void)(((e.col) = 0));
    (void)(parser_expr_set_common_zeros(&(e)));
    (void)(ast_ast_arena_expr_set(arena, ref, e));
    return ref;
  }
}
int32_t parser_expr_wrap_in_return(struct ast_ASTArena * arena, int32_t type_ref, int32_t inner_ref) {
  {
    if (ast_ref_is_null(inner_ref)) {
      return 0;
    }
    struct ast_Expr inner = ast_ast_arena_expr_get(arena, inner_ref);
    if (((inner.kind) ==41)) {
      return inner_ref;
    }
    int32_t wrap = ast_ast_arena_expr_alloc(arena);
    if ((wrap ==0)) {
      return 0;
    }
    struct ast_Expr rwe = ast_ast_arena_expr_get(arena, wrap);
    (void)(((rwe.kind) = 41));
    (void)(((rwe.line) = 0));
    (void)(((rwe.col) = 0));
    (void)(((rwe.int_val) = 0));
    (void)(parser_expr_set_common_zeros(&(rwe)));
    (void)(((rwe.resolved_type_ref) = type_ref));
    (void)(((rwe.unary_operand_ref) = inner_ref));
    (void)(ast_ast_arena_expr_set(arena, wrap, rwe));
    return wrap;
  }
}
int parser_should_wrap_func_tail_in_return(struct ast_ASTArena * arena, struct parser_OneFuncResult * res, int32_t type_ref) {
  {
    if (ast_ref_is_null(type_ref)) {
      return 0;
    }
    struct ast_Type rtw = ast_ast_arena_type_get(arena, type_ref);
    if (((rtw.kind) ==16)) {
      return 0;
    }
    return (res->has_explicit_return_kw);
  }
}
extern void parser_parse_match_subject_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_match_subject_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_match_subject_into_glue(arena, lex, source, out));
}
extern void parser_parse_match_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_match_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_match_into_glue(arena, lex, source, out));
}
extern void parser_parse_at_simd_builtin_into_glue(struct ast_ASTArena * arena, struct lexer_LexerResult r0, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_at_simd_builtin_into(struct ast_ASTArena * arena, struct lexer_LexerResult r0, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_at_simd_builtin_into_glue(arena, r0, source, out));
}
extern void parser_parse_primary_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_primary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_primary_into_glue(arena, lex, source, out));
}
extern void parser_parse_as_suffix_into_glue(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_as_suffix_into(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_as_suffix_into_glue(arena, source, out));
}
extern void parser_parse_unary_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_unary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_unary_into_glue(arena, lex, source, out));
}
extern void parser_parse_cast_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_cast_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_cast_into_glue(arena, lex, source, out));
}
extern void parser_parse_term_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_term_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_term_into_glue(arena, lex, source, out));
}
extern void parser_parse_addsub_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_addsub_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_addsub_into_glue(arena, lex, source, out));
}
extern void parser_parse_shift_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_shift_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_shift_into_glue(arena, lex, source, out));
}
extern void parser_parse_relcompare_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_relcompare_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_relcompare_into_glue(arena, lex, source, out));
}
extern void parser_parse_compare_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_compare_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_compare_into_glue(arena, lex, source, out));
}
extern void parser_parse_bitand_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_bitand_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_bitand_into_glue(arena, lex, source, out));
}
extern void parser_parse_bitxor_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_bitxor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_bitxor_into_glue(arena, lex, source, out));
}
extern void parser_parse_bitor_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_bitor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_bitor_into_glue(arena, lex, source, out));
}
extern void parser_parse_logand_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_logand_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_logand_into_glue(arena, lex, source, out));
}
extern void parser_parse_logor_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_logor_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_logor_into_glue(arena, lex, source, out));
}
extern void parser_parse_ternary_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_ternary_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_ternary_into_glue(arena, lex, source, out));
}
int parser_is_compound_assign_token(enum token_TokenKind kind) {
  if ((kind ==106)) {
    return 1;
  }
  if ((kind ==107)) {
    return 1;
  }
  if ((kind ==108)) {
    return 1;
  }
  if ((kind ==109)) {
    return 1;
  }
  if ((kind ==110)) {
    return 1;
  }
  if ((kind ==111)) {
    return 1;
  }
  if ((kind ==112)) {
    return 1;
  }
  if ((kind ==113)) {
    return 1;
  }
  if ((kind ==114)) {
    return 1;
  }
  if ((kind ==115)) {
    return 1;
  }
  return 0;
}
extern enum ast_ExprKind compound_assign_token_to_expr_kind_from_glue(enum token_TokenKind kind);
enum ast_ExprKind parser_compound_assign_token_to_expr_kind(enum token_TokenKind kind) {
  return compound_assign_token_to_expr_kind_from_glue(kind);
}
extern int pipeline_expr_ref_is_assign_lvalue(struct ast_ASTArena * arena, int32_t expr_ref);
int parser_expr_ref_is_assign_lvalue(struct ast_ASTArena * arena, int32_t expr_ref) {
  return pipeline_expr_ref_is_assign_lvalue(arena, expr_ref);
  return 0;
}
extern void parser_parse_assign_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_assign_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_assign_into_glue(arena, lex, source, out));
}
void parser_parse_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_assign_into(arena, lex, source, out));
}
extern void parser_finish_struct_lit_from_type_ident_into_glue(struct ast_ASTArena * arena, int32_t lit_ref, struct lexer_Lexer lex_in_brace, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_finish_struct_lit_from_type_ident_into(struct ast_ASTArena * arena, int32_t lit_ref, struct lexer_Lexer lex_in_brace, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_finish_struct_lit_from_type_ident_into_glue(arena, lit_ref, lex_in_brace, source, out));
}
extern void parser_parse_cond_expr_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out);
void parser_parse_cond_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_cond_expr_into_glue(arena, lex_start, source, out));
}
void parser_parse_expr_with_leading_int_as_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, struct xlang_slice_uint8_t * source, struct parser_ParseExprResult * out) {
  (void)(parser_parse_cond_expr_into(arena, lex_start, source, out));
}
void parser_parse_expr_with_leading_int_as_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_expr_with_leading_int_as_into(arena, lex_start, &(slice), out));
  }
}
extern int parser_fill_block_const_let_from_res_glue(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t type_ref);
int parser_fill_block_const_let_from_res(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t type_ref) {
  return parser_fill_block_const_let_from_res_glue(arena, block_ref, res, type_ref);
  return 0;
}
extern int parser_append_block_lets_from_res_glue(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t let_base, int32_t type_ref);
int parser_append_block_lets_from_res(struct ast_ASTArena * arena, int32_t block_ref, struct parser_OneFuncResult * res, int32_t let_base, int32_t type_ref) {
  return parser_append_block_lets_from_res_glue(arena, block_ref, res, let_base, type_ref);
  return 0;
}
extern int parser_parse_if_stmt_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, int32_t * out_cond, int32_t * out_then, int32_t * out_else, struct lexer_Lexer * lex_out);
extern void parser_realign_lex_after_if_stmt_onefunc_glue(struct lexer_Lexer * lex, struct xlang_slice_uint8_t * source);
int parser_parse_if_stmt_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, int32_t * out_cond, int32_t * out_then, int32_t * out_else, struct lexer_Lexer * lex_out) {
  return parser_parse_if_stmt_into_glue(arena, lex_at_if, source, type_ref, out_cond, out_then, out_else, lex_out);
  return 0;
}
/* wave1226: heap OneFuncResult scratch — always release+free after body.
 * Root: calloc without ast_pool_onefunc_release filled MAX_ONEFUNC_SIDECARS
 * after large files; next file soft-skipped defined functions.
 * PLATFORM: SHARED */
static void parser_parse_block_into_with_scratch(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseBlockResult * out, struct parser_OneFuncResult * temp);
void parser_parse_block_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseBlockResult * out) {
  {
    size_t scratch_sz = pipeline_sizeof_onefunc_result();
    uint8_t * scratch_raw = calloc(1, scratch_sz);
    if ((scratch_raw ==((uint8_t *)(0)))) {
      (void)(((out->ok) = 0));
      return;
    }
    struct parser_OneFuncResult * temp = ((struct parser_OneFuncResult *)(scratch_raw));
    parser_parse_block_into_with_scratch(arena, lex_after_lbrace, source, type_ref, out, temp);
    (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(temp)));
    free(scratch_raw);
  }
}
static void parser_parse_block_into_with_scratch(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseBlockResult * out, struct parser_OneFuncResult * temp) {
  {
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(temp)));
    (void)(((temp->ok) = 1));
    (void)(((temp->next_lex) = lex_after_lbrace));
    (void)(((temp->return_var_name_len) = 0));
    (void)(((temp->return_expr_ref) = 0));
    (void)(((temp->num_src_stmt_order) = 0));
    (void)(((temp->num_src_body_expr_stmts) = 0));
    (void)(((temp->func_return_type_ref) = 0));
    struct lexer_Lexer lex_cur = lex_after_lbrace;
    if (!(parser_parse_body_lets_into(arena, lex_after_lbrace, source, temp, &(lex_cur)))) {
      (void)(((out->ok) = 0));
      return;
    }
    int32_t block_ref = ast_ast_arena_block_alloc(arena);
    if ((block_ref ==0)) {
      (void)(((out->ok) = 0));
      return;
    }
    struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
    (void)(((b.num_consts) = 0));
    (void)(((b.num_lets) = 0));
    (void)(((b.num_early_lets) = 0));
    (void)(((b.num_loops) = 0));
    (void)(((b.num_for_loops) = 0));
    (void)(((b.num_if_stmts) = 0));
    (void)(((b.num_regions) = 0));
    (void)(((b.num_defers) = 0));
    (void)(((b.num_labeled_stmts) = 0));
    (void)(((b.num_expr_stmts) = 0));
    (void)(((b.final_expr_ref) = 0));
    (void)(((b.num_stmt_order) = 0));
    (void)(((b.parent_block_ref) = 0));
    (void)(ast_ast_arena_block_set(arena, block_ref, b));
    if (!(parser_fill_block_const_let_from_res(arena, block_ref, temp, type_ref))) {
      (void)(((out->ok) = 0));
      return;
    }
    (void)((b = ast_ast_arena_block_get(arena, block_ref)));
    int32_t block_prefix_lets = (b.num_lets);
    int32_t ci = 0;
    while ((ci < (b.num_consts))) {
      if ((pipeline_block_append_stmt_order(arena, block_ref, 0, ci) < 0)) {
        (void)(((out->ok) = 0));
        return;
      }
      (void)((ci = (ci + 1)));
    }
    int32_t li = 0;
    while ((li < (b.num_lets))) {
      if ((pipeline_block_append_stmt_order(arena, block_ref, 1, li) < 0)) {
        (void)(((out->ok) = 0));
        return;
      }
      (void)((li = (li + 1)));
    }
    struct lexer_LexerResult r_peek_blk = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    (void)(lexer_next_into(&(r_peek_blk), lex_cur, source));
    struct lexer_LexerResult r = r_peek_blk;
    (void)((lex_cur = parser_rewind_lex_for_following_stmt(lex_cur, r_peek_blk)));
    int stmt_tok_ready = 1;
    int32_t pb_break = 0;
    struct lexer_Lexer stmt_start = (struct lexer_Lexer){ .pos = ((size_t)(0)), .line = 0, .col = 0 };
    struct parser_ParseExprResult expr_stmt_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = stmt_start };
    struct lexer_LexerResult rpeek_fe = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    int32_t ex_pool_i = 0;
    while ((1 ==1)) {
      if ((pb_break !=0)) {
        break;
      }
      if (!(stmt_tok_ready)) {
        (void)(lexer_next_into(&(r), lex_cur, source));
      }
      (void)((stmt_tok_ready = 0));
      if ((((r.tok).kind) ==85)) {
        break;
      }
      if ((((r.tok).kind) ==0)) {
        (void)(((out->ok) = 0));
        return;
      }
      if ((((r.tok).kind) ==82)) {
        (void)((lex_cur = parser_rewind_lex_for_lparen_control_stmt(lex_cur, r, source)));
        (void)(lexer_next_into(&(r), lex_cur, source));
      }
      if (((((r.tok).kind) ==2) || (((r.tok).kind) ==3))) {
        /* Mid-body let/const: copy both pools; record kind=0 then kind=1 (prefix face). */
        int32_t let_base_mid = (b.num_lets);
        int32_t const_base_mid = (b.num_consts);
        (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(temp)));
        (void)(((temp->num_lets) = 0));
        (void)(((temp->num_consts) = 0));
        int32_t kw_back_mid = 3;
        if ((((r.tok).kind) ==3)) {
          (void)((kw_back_mid = 5));
        }
        struct lexer_Lexer lex_mid_let = (struct lexer_Lexer){ .pos = parser_lexer_pos_before_run(((r.next_lex).pos), kw_back_mid), .line = ((r.tok).line), .col = ((r.tok).col) };
        if (!(parser_parse_body_lets_into(arena, lex_mid_let, source, temp, &(lex_cur)))) {
          (void)(((out->ok) = 0));
          return;
        }
        if (!(parser_append_block_lets_from_res(arena, block_ref, temp, 0, type_ref))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        int32_t ci_mid = const_base_mid;
        while ((ci_mid < (b.num_consts))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 0, ci_mid) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((ci_mid = (ci_mid + 1)));
        }
        int32_t pi_mid = let_base_mid;
        while ((pi_mid < (b.num_lets))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 1, pi_mid) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((pi_mid = (pi_mid + 1)));
        }
        (void)(lexer_next_into(&(r), lex_cur, source));
        (void)((stmt_tok_ready = 1));
        continue;
      }
      /* wave379: bare goto target; (TOKEN_GOTO=48, IDENT=59, SEMICOLON=95). stmt_order kind=7. */
      if ((((r.tok).kind) ==48)) {
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=59)) {
          (void)(((out->ok) = 0));
          return;
        }
        int32_t goto_len_bare = ((r.tok).ident_len);
        size_t goto_start_bare = (r.token_start);
        if ((goto_start_bare ==0)) {
          (void)((goto_start_bare = parser_lexer_pos_before_run(((r.next_lex).pos), goto_len_bare)));
        }
        uint8_t goto_row_bare[128] = {};
        (void)(parser_copy_slice_to_param32(source, goto_start_bare, goto_len_bare, &((goto_row_bare)[0])));
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) ==95)) {
          (void)((lex_cur = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex_cur, source));
        }
        int32_t li_bare = pipeline_block_append_labeled(arena, block_ref, 0, 1, goto_len_bare, 0);
        if ((li_bare < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(pipeline_block_labeled_set_names(arena, block_ref, li_bare, ((uint8_t *)(0)), 0, &((goto_row_bare)[0]), goto_len_bare));
        if ((pipeline_block_append_stmt_order(arena, block_ref, 7, li_bare) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        continue;
      }
      if (parser_token_is_label_start(r, source)) {
        int32_t label_len_blk = ((r.tok).ident_len);
        size_t label_start_blk = (r.token_start);
        if ((label_start_blk ==0)) {
          (void)((label_start_blk = parser_lexer_pos_before_run(((r.next_lex).pos), label_len_blk)));
        }
        struct lexer_LexerResult colon_blk = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
        (void)(lexer_next_into(&(colon_blk), (r.next_lex), source));
        (void)((lex_cur = (colon_blk.next_lex)));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) ==48)) {
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)(lexer_next_into(&(r), lex_cur, source));
          if ((((r.tok).kind) !=59)) {
            (void)(((out->ok) = 0));
            return;
          }
          int32_t goto_len_blk = ((r.tok).ident_len);
          size_t goto_start_blk = (r.token_start);
          if ((goto_start_blk ==0)) {
            (void)((goto_start_blk = parser_lexer_pos_before_run(((r.next_lex).pos), goto_len_blk)));
          }
          uint8_t goto_row_blk[128] = {};
          (void)(parser_copy_slice_to_param32(source, goto_start_blk, goto_len_blk, &((goto_row_blk)[0])));
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)(lexer_next_into(&(r), lex_cur, source));
          if ((((r.tok).kind) ==95)) {
            (void)((lex_cur = (r.next_lex)));
            (void)(lexer_next_into(&(r), lex_cur, source));
          }
          uint8_t label_row_blk[128] = {};
          (void)(parser_copy_slice_to_param32(source, label_start_blk, label_len_blk, &((label_row_blk)[0])));
          int32_t li_lab = pipeline_block_append_labeled(arena, block_ref, label_len_blk, 0, 0, 0);
          if ((li_lab < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)(pipeline_block_labeled_set_names(arena, block_ref, li_lab, &((label_row_blk)[0]), label_len_blk, ((uint8_t *)(0)), 0));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 7, li_lab) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          int32_t li_goto = pipeline_block_append_labeled(arena, block_ref, 0, 1, goto_len_blk, 0);
          if ((li_goto < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)(pipeline_block_labeled_set_names(arena, block_ref, li_goto, ((uint8_t *)(0)), 0, &((goto_row_blk)[0]), goto_len_blk));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 7, li_goto) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          continue;
        }
        if ((((r.tok).kind) ==11)) {
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          struct parser_ParseExprResult ret_val_lbl = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
          (void)(lexer_next_into(&(r), lex_cur, source));
          if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
            (void)(parser_parse_expr_into(arena, lex_cur, source, &(ret_val_lbl)));
            if (!((ret_val_lbl.ok))) {
              (void)(((out->ok) = 0));
              return;
            }
            (void)((lex_cur = (ret_val_lbl.next_lex)));
            (void)(lexer_next_into(&(r), lex_cur, source));
          }
          if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
            (void)(((out->ok) = 0));
            return;
          }
          if ((((r.tok).kind) ==95)) {
            (void)((lex_cur = (r.next_lex)));
            (void)(lexer_next_into(&(r), lex_cur, source));
          }
          uint8_t label_row_ret[128] = {};
          (void)(parser_copy_slice_to_param32(source, label_start_blk, label_len_blk, &((label_row_ret)[0])));
          int32_t ret_operand = 0;
          if ((ret_val_lbl.ok)) {
            (void)((ret_operand = (ret_val_lbl.expr_ref)));
          }
          int32_t li_ret = pipeline_block_append_labeled(arena, block_ref, label_len_blk, 0, 0, ret_operand);
          if ((li_ret < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)(pipeline_block_labeled_set_names(arena, block_ref, li_ret, &((label_row_ret)[0]), label_len_blk, ((uint8_t *)(0)), 0));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 7, li_ret) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          continue;
        }
        /* wave379: pure L: label def; fall through to next stmt */
        {
          uint8_t label_row_pure[128] = {};
          (void)(parser_copy_slice_to_param32(source, label_start_blk, label_len_blk, &((label_row_pure)[0])));
          int32_t li_pure = pipeline_block_append_labeled(arena, block_ref, label_len_blk, 0, 0, 0);
          if ((li_pure < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)(pipeline_block_labeled_set_names(arena, block_ref, li_pure, &((label_row_pure)[0]), label_len_blk, ((uint8_t *)(0)), 0));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 7, li_pure) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((stmt_tok_ready = 1));
          continue;
        }
      }
      if ((((r.tok).kind) ==11)) {
        /* wave655: return operand + ASI (same as expr-stmt); no double-advance after `;`. */
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        struct parser_ParseExprResult ret_val_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        int return_ends_block = 0;
        (void)(lexer_next_into(&(r), lex_cur, source));
        if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
          (void)(parser_parse_expr_into(arena, lex_cur, source, &(ret_val_res)));
          if (!((ret_val_res.ok))) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((lex_cur = (ret_val_res.next_lex)));
          if ((parser_advance_past_stmt_semicolon_into(&(r), lex_cur, source) ==0)) {
            (void)(((out->ok) = 0));
            return;
          }
        }
        if ((((r.tok).kind) ==95)) {
          (void)((lex_cur = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex_cur, source));
        }
        int32_t ret_ref = ast_ast_arena_expr_alloc(arena);
        if ((ret_ref ==0)) {
          (void)(((out->ok) = 0));
          return;
        }
        struct ast_Expr re = ast_ast_arena_expr_get(arena, ret_ref);
        (void)(((re.kind) = 41));
        (void)(((re.line) = 0));
        (void)(((re.col) = 0));
        (void)(parser_expr_set_common_zeros(&(re)));
        if ((ret_val_res.ok)) {
          (void)(((re.unary_operand_ref) = (ret_val_res.expr_ref)));
        }
        (void)(ast_ast_arena_expr_set(arena, ret_ref, re));
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((return_ends_block = (((r.tok).kind) ==85)));
        if (return_ends_block) {
          (void)(((b.final_expr_ref) = ret_ref));
          (void)(ast_ast_arena_block_set(arena, block_ref, b));
          (void)((pb_break = 1));
        } else {
          int32_t ret_ex_i = pipeline_block_append_expr_stmt(arena, block_ref, ret_ref);
          if ((ret_ex_i < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          if ((pipeline_block_append_stmt_order(arena, block_ref, 2, ret_ex_i) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
          (void)((stmt_tok_ready = 1));
        }
        continue;
      }
      if ((((r.tok).kind) ==7)) {
        int32_t cond_ref_blk = 0;
        struct parser_ParseBlockResult block_res_blk = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t while_idx_blk = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)((cond_ref_blk = parser_alloc_true_bool_lit(arena)));
        if ((cond_ref_blk ==0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((block_res_blk = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_blk)));
        if (!((block_res_blk.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((while_idx_blk = pipeline_block_append_while(arena, block_ref, cond_ref_blk, (block_res_blk.block_ref))));
        if ((while_idx_blk < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 3, while_idx_blk) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res_blk.next_lex)));
        (void)((stmt_tok_ready = 0));
        continue;
      }
      if ((((r.tok).kind) ==6)) {
        struct lexer_Lexer loop_cond_start = lex_cur;
        struct parser_ParseExprResult expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        int32_t cond_ref = 0;
        struct parser_ParseBlockResult block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t while_idx = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        /* wave361/wave650: bare while cond (docs/03); do not strip LPAREN (82). */
        (void)((lex_cur = parser_lex_at_token_from_result(r)));
        (void)((loop_cond_start = lex_cur));
        (void)((expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = loop_cond_start }));
        (void)(parser_parse_cond_expr_into(arena, loop_cond_start, source, &(expr_res)));
        if (!((expr_res.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((cond_ref = (expr_res.expr_ref)));
        (void)((lex_cur = (expr_res.next_lex)));
        if ((parser_advance_past_cond_rparen_into(&(r), lex_cur, source) ==0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)((block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res)));
        if (!((block_res.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((while_idx = pipeline_block_append_while(arena, block_ref, cond_ref, (block_res.block_ref))));
        if ((while_idx < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 3, while_idx) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res.next_lex)));
        (void)((stmt_tok_ready = 0));
        continue;
      }
      if ((((r.tok).kind) ==8)) {
        int32_t init_ref = 0;
        int32_t cond_ref = 0;
        int32_t step_ref = 0;
        struct parser_ParseBlockResult block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t for_idx = 0;
        struct parser_ParseExprResult expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        struct parser_ParseExprResult expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        struct parser_ParseExprResult expr_res_fs = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        int32_t cond_expr_ref = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=82)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)(lexer_next_into(&(r), lex_cur, source));
        /* wave347: for-init let (TOKEN_LET=2) — hoist via body-lets face; init_ref=0. */
        int for_past_init_semi = 0;
        if ((((r.tok).kind) !=95)) {
          if ((((r.tok).kind) ==2)) {
            int32_t let_base_fi = (b.num_lets);
            (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(temp)));
            (void)(((temp->num_lets) = 0));
            (void)(((temp->num_consts) = 0));
            struct lexer_Lexer lex_fi_let = (struct lexer_Lexer){
              .pos = parser_lexer_pos_before_run(((r.next_lex).pos), 3),
              .line = ((r.tok).line),
              .col = ((r.tok).col)
            };
            if (!(parser_parse_body_lets_into(arena, lex_fi_let, source, temp, &(lex_cur)))) {
              (void)(((out->ok) = 0));
              return;
            }
            if (!(parser_append_block_lets_from_res(arena, block_ref, temp, 0, type_ref))) {
              (void)(((out->ok) = 0));
              return;
            }
            (void)((b = ast_ast_arena_block_get(arena, block_ref)));
            int32_t pi_fi = let_base_fi;
            while ((pi_fi < (b.num_lets))) {
              if ((pipeline_block_append_stmt_order(arena, block_ref, 1, pi_fi) < 0)) {
                (void)(((out->ok) = 0));
                return;
              }
              (void)((pi_fi = (pi_fi + 1)));
            }
            (void)((init_ref = 0));
            (void)((for_past_init_semi = 1));
            (void)(lexer_next_into(&(r), lex_cur, source));
          } else {
            /* wave701: range-for in block path (nested for). G.7 ≡ onefunc desugar. */
            int range_for_done_blk = 0;
            if ((((r.tok).kind) == token_TokenKind_TOKEN_IDENT)) {
              struct lexer_LexerResult r_peek_b;
              (void)(lexer_next_into(&(r_peek_b), (r.next_lex), source));
              if ((((r_peek_b.tok).kind) == token_TokenKind_TOKEN_COLON)) {
                uint8_t rf_name[128];
                int32_t rf_nlen = ((r.tok).ident_len);
                size_t rf_nstart = (r.token_start);
                int32_t rf_ni = 0;
                int32_t lo_ref = 0;
                int32_t hi_ref = 0;
                int32_t v1 = 0;
                int32_t v2 = 0;
                int32_t v3 = 0;
                int32_t one_ref = 0;
                int32_t lt_ref = 0;
                int32_t add_ref = 0;
                int32_t asg_ref = 0;
                int32_t i32ty = 0;
                int32_t let_i = 0;
                struct ast_Expr ve;
                if (rf_nlen > 127) rf_nlen = 127;
                for (rf_ni = 0; rf_ni < 128; rf_ni++) rf_name[rf_ni] = 0;
                for (rf_ni = 0; rf_ni < rf_nlen && rf_nstart + (size_t)rf_ni < (source->length); rf_ni++)
                  rf_name[rf_ni] = (source->data)[rf_nstart + rf_ni];
                (void)((lex_cur = (r_peek_b.next_lex)));
                (void)((expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
                (void)(parser_parse_expr_into(arena, lex_cur, source, &(expr_res_fi)));
                if (!((expr_res_fi.ok))) { (void)(((out->ok) = 0)); return; }
                lo_ref = (expr_res_fi.expr_ref);
                (void)((lex_cur = (expr_res_fi.next_lex)));
                (void)(lexer_next_into(&(r), lex_cur, source));
                if ((((r.tok).kind) == token_TokenKind_TOKEN_DOTDOT)) {
                  (void)((lex_cur = (r.next_lex)));
                } else if ((((r.tok).kind) == token_TokenKind_TOKEN_DOT)) {
                  (void)((lex_cur = (r.next_lex)));
                  (void)(lexer_next_into(&(r), lex_cur, source));
                  if ((((r.tok).kind) == token_TokenKind_TOKEN_DOT)) {
                    (void)((lex_cur = (r.next_lex)));
                  } else {
                    int32_t run = 1;
                    if ((((r.tok).kind) == token_TokenKind_TOKEN_IDENT)) run = ((r.tok).ident_len);
                    if ((r.token_start) > 0)
                      (void)((lex_cur = (struct lexer_Lexer){ .pos = (r.token_start), .line = ((r.tok).line), .col = ((r.tok).col) }));
                    else
                      (void)((lex_cur = (struct lexer_Lexer){ .pos = parser_lexer_pos_before_run(((r.next_lex).pos), run), .line = ((r.tok).line), .col = ((r.tok).col) }));
                  }
                } else {
                  (void)(((out->ok) = 0)); return;
                }
                (void)((expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
                (void)(parser_parse_expr_into(arena, lex_cur, source, &(expr_res_fc)));
                if (!((expr_res_fc.ok))) { (void)(((out->ok) = 0)); return; }
                hi_ref = (expr_res_fc.expr_ref);
                (void)((lex_cur = (expr_res_fc.next_lex)));
                (void)(lexer_next_into(&(r), lex_cur, source));
                if ((((r.tok).kind) !=83)) { (void)(((out->ok) = 0)); return; }
                (void)((lex_cur = (r.next_lex)));
                (void)(lexer_next_into(&(r), lex_cur, source));
                if ((((r.tok).kind) !=84)) { (void)(((out->ok) = 0)); return; }
                (void)((lex_cur = (r.next_lex)));
                (void)((block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
                (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res)));
                if (!((block_res.ok))) { (void)(((out->ok) = 0)); return; }
                i32ty = ast_ast_arena_type_alloc(arena);
                if (i32ty > 0) {
                  struct ast_Type ti32 = ast_ast_arena_type_get(arena, i32ty);
                  ti32.kind = ast_TypeKind_TYPE_I32;
                  (void)(ast_ast_arena_type_set(arena, i32ty, ti32));
                }
                let_i = (b.num_lets);
                if (pipeline_block_append_let(arena, block_ref, rf_name, rf_nlen, i32ty, lo_ref) < 0) {
                  (void)(((out->ok) = 0)); return;
                }
                (void)((b = ast_ast_arena_block_get(arena, block_ref)));
                if (pipeline_block_append_stmt_order(arena, block_ref, 1, let_i) < 0) {
                  (void)(((out->ok) = 0)); return;
                }
                v1 = ast_ast_arena_expr_alloc(arena);
                v2 = ast_ast_arena_expr_alloc(arena);
                v3 = ast_ast_arena_expr_alloc(arena);
                one_ref = ast_ast_arena_expr_alloc(arena);
                lt_ref = ast_ast_arena_expr_alloc(arena);
                add_ref = ast_ast_arena_expr_alloc(arena);
                asg_ref = ast_ast_arena_expr_alloc(arena);
                if (!(v1 && v2 && v3 && one_ref && lt_ref && add_ref && asg_ref)) {
                  (void)(((out->ok) = 0)); return;
                }
                ve = ast_ast_arena_expr_get(arena, v1);
                ve.kind = 3; ve.var_name_len = rf_nlen;
                for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                ast_ast_arena_expr_set(arena, v1, ve);
                ve = ast_ast_arena_expr_get(arena, v2);
                ve.kind = 3; ve.var_name_len = rf_nlen;
                for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                ast_ast_arena_expr_set(arena, v2, ve);
                ve = ast_ast_arena_expr_get(arena, v3);
                ve.kind = 3; ve.var_name_len = rf_nlen;
                for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                ast_ast_arena_expr_set(arena, v3, ve);
                ve = ast_ast_arena_expr_get(arena, one_ref);
                ve.kind = 0; ve.int_val = 1; ve.line = 0; ve.col = 0;
                ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                ast_ast_arena_expr_set(arena, one_ref, ve);
                ve = ast_ast_arena_expr_get(arena, lt_ref);
                ve.kind = 16; ve.binop_left_ref = v1; ve.binop_right_ref = hi_ref;
                ve.line = 0; ve.col = 0; ve.int_val = 0;
                ast_ast_arena_expr_set(arena, lt_ref, ve);
                ve = ast_ast_arena_expr_get(arena, add_ref);
                ve.kind = 4; ve.binop_left_ref = v2; ve.binop_right_ref = one_ref;
                ve.line = 0; ve.col = 0; ve.int_val = 0;
                ast_ast_arena_expr_set(arena, add_ref, ve);
                ve = ast_ast_arena_expr_get(arena, asg_ref);
                ve.kind = 28; ve.binop_left_ref = v3; ve.binop_right_ref = add_ref;
                ve.line = 0; ve.col = 0; ve.int_val = 0;
                ast_ast_arena_expr_set(arena, asg_ref, ve);
                for_idx = pipeline_block_append_for(arena, block_ref, 0, lt_ref, asg_ref, (block_res.block_ref));
                if (for_idx < 0) { (void)(((out->ok) = 0)); return; }
                if (pipeline_block_append_stmt_order(arena, block_ref, 4, for_idx) < 0) {
                  (void)(((out->ok) = 0)); return;
                }
                (void)((b = ast_ast_arena_block_get(arena, block_ref)));
                (void)((lex_cur = (block_res.next_lex)));
                (void)((stmt_tok_ready = 0));
                range_for_done_blk = 1;
              }
            }
            if (range_for_done_blk) {
              continue;
            }
            (void)((expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
            (void)(parser_parse_expr_into(arena, lex_cur, source, &(expr_res_fi)));
            if (!((expr_res_fi.ok))) {
              (void)(((out->ok) = 0));
              return;
            }
            (void)((init_ref = (expr_res_fi.expr_ref)));
            (void)((lex_cur = (expr_res_fi.next_lex)));
            (void)(lexer_next_into(&(r), lex_cur, source));
          }
        }
        if (!(for_past_init_semi)) {
          if ((((r.tok).kind) !=95)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((lex_cur = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex_cur, source));
        }
        if ((((r.tok).kind) !=95)) {
          (void)((expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
          (void)(parser_parse_expr_into(arena, lex_cur, source, &(expr_res_fc)));
          if (!((expr_res_fc.ok))) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((cond_ref = (expr_res_fc.expr_ref)));
          (void)((lex_cur = (expr_res_fc.next_lex)));
          (void)(lexer_next_into(&(r), lex_cur, source));
        }
        if ((((r.tok).kind) !=95)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=83)) {
          (void)((expr_res_fs = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
          (void)(parser_parse_expr_into(arena, lex_cur, source, &(expr_res_fs)));
          if (!((expr_res_fs.ok))) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((step_ref = (expr_res_fs.expr_ref)));
          (void)((lex_cur = (expr_res_fs.next_lex)));
          (void)(lexer_next_into(&(r), lex_cur, source));
        }
        if ((((r.tok).kind) !=83)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)((block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res)));
        if (!((block_res.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((cond_ref ==0)) {
          (void)((cond_expr_ref = ast_ast_arena_expr_alloc(arena)));
          if ((cond_expr_ref !=0)) {
            struct ast_Expr ce = ast_ast_arena_expr_get(arena, cond_expr_ref);
            (void)(((ce.kind) = 2));
            (void)(((ce.int_val) = 1));
            (void)(((ce.line) = 0));
            (void)(((ce.col) = 0));
            (void)(parser_expr_set_common_zeros(&(ce)));
            (void)(ast_ast_arena_expr_set(arena, cond_expr_ref, ce));
            (void)((cond_ref = cond_expr_ref));
          }
        }
        (void)((for_idx = pipeline_block_append_for(arena, block_ref, init_ref, cond_ref, step_ref, (block_res.block_ref))));
        if ((for_idx < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 4, for_idx) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res.next_lex)));
        (void)((stmt_tok_ready = 0));
        continue;
      }
      if ((((r.tok).kind) ==13)) {
        struct parser_ParseBlockResult block_res_def = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t def_i = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((lex_cur = (r.next_lex)));
        (void)((block_res_def = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_def)));
        if (!((block_res_def.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((def_i = pipeline_block_append_defer(arena, block_ref, (block_res_def.block_ref))));
        if ((def_i < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res_def.next_lex)));
        /* Optional `;` after defer {…} (compound ASI). Extra-arm dest
         * `{ defer { k = 1 }; { h: e } }` used to P001. No-semi dest
         * stays stmt_tok_ready. kind 95 = TOKEN_SEMICOLON.
         * PLATFORM: SHARED — twin of parser.x parse_block defer. */
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)((stmt_tok_ready = 0));
        } else {
          (void)((stmt_tok_ready = 1));
        }
        continue;
      }
      if ((((r.tok).kind) ==17)) {
        int32_t cap_ref = 0;
        struct parser_ParseExprResult cap_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur };
        struct parser_ParseBlockResult block_res_wa = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t wa_pool_i = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=82)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)((cap_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_expr_into(arena, lex_cur, source, &(cap_res)));
        if ((!((cap_res.ok)) || ((cap_res.expr_ref) ==0))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((cap_ref = (cap_res.expr_ref)));
        (void)((lex_cur = (cap_res.next_lex)));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=83)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)((block_res_wa = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_wa)));
        if (!((block_res_wa.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((wa_pool_i = pipeline_block_append_with_arena(arena, block_ref, cap_ref, (block_res_wa.block_ref))));
        if ((wa_pool_i < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 6, wa_pool_i) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res_wa.next_lex)));
        /* Optional `;` after with_arena(cap) {…} (compound ASI). Extra-arm
         * dest `{ with_arena(n) { k = 1 }; { h: e } }` used to P001.
         * No-semi dest stays stmt_tok_ready. kind 95 = TOKEN_SEMICOLON.
         * Do not realign (would skip dest). PLATFORM: SHARED. */
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)((stmt_tok_ready = 0));
        } else {
          (void)((stmt_tok_ready = 1));
        }
        continue;
      }
      if ((((r.tok).kind) ==16)) {
        uint8_t reg_label_blk[128] = {};
        int32_t reg_label_len_blk = 0;
        struct parser_ParseBlockResult block_res_reg = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t reg_pool_i = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=59)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(parser_copy_slice_to_name64(source, (r.token_start), ((r.tok).ident_len), &((reg_label_blk)[0])));
        (void)((reg_label_len_blk = ((r.tok).ident_len)));
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) !=84)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)((block_res_reg = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_reg)));
        if (!((block_res_reg.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((reg_pool_i = pipeline_block_append_region(arena, block_ref, &((reg_label_blk)[0]), reg_label_len_blk, (block_res_reg.block_ref))));
        if ((reg_pool_i < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 6, reg_pool_i) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((lex_cur = (block_res_reg.next_lex)));
        /* Optional `;` after region label {…} (compound ASI). Extra-arm dest
         * `{ region foo { k = 1 }; { h: e } }` used to P001. No-semi dest
         * stays stmt_tok_ready. kind 95 = TOKEN_SEMICOLON.
         * Do not realign (would skip dest). PLATFORM: SHARED. */
        (void)(lexer_next_into(&(r), lex_cur, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)((stmt_tok_ready = 0));
        } else {
          (void)((stmt_tok_ready = 1));
        }
        continue;
      }
      if (((((r.tok).kind) ==59) && (((r.tok).ident_len) ==6))) {
        uint8_t unsafe_nm[128] = {};
        (void)(parser_copy_slice_to_name64(source, (r.token_start), ((r.tok).ident_len), &((unsafe_nm)[0])));
        if ((((((((unsafe_nm)[0] ==117) && ((unsafe_nm)[1] ==110)) && ((unsafe_nm)[2] ==115)) && ((unsafe_nm)[3] ==97)) && ((unsafe_nm)[4] ==102)) && ((unsafe_nm)[5] ==101))) {
          struct parser_ParseBlockResult block_res_unsafe = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
          int32_t unsafe_pool_i = 0;
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)(lexer_next_into(&(r), lex_cur, source));
          if ((((r.tok).kind) !=84)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex_cur), r));
          (void)((block_res_unsafe = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
          (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_unsafe)));
          if (!((block_res_unsafe.ok))) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((unsafe_pool_i = pipeline_block_append_unsafe(arena, block_ref, (block_res_unsafe.block_ref))));
          if ((unsafe_pool_i < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          if ((pipeline_block_append_stmt_order(arena, block_ref, 6, unsafe_pool_i) < 0)) {
            (void)(((out->ok) = 0));
            return;
          }
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
          (void)((lex_cur = (block_res_unsafe.next_lex)));
          /* Optional `;` after unsafe {…} (compound ASI). Extra-arm dest
           * `{ unsafe { k = 1 }; { h: e } }` used to P001. No-semi dest_if
           * extra-arm region stays stmt_tok_ready. kind 95 = TOKEN_SEMICOLON.
           * PLATFORM: SHARED — twin of parser.x parse_block unsafe. */
          (void)(lexer_next_into(&(r), lex_cur, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex_cur), r));
            (void)((stmt_tok_ready = 0));
          } else {
            (void)((stmt_tok_ready = 1));
          }
          continue;
        }
      }
      if ((((r.tok).kind) ==4)) {
        struct lexer_Lexer if_start = parser_lex_at_token_from_result(r);
        int32_t if_cond = 0;
        int32_t if_then = 0;
        int32_t if_else = 0;
        if (!(parser_parse_if_stmt_into(arena, if_start, source, type_ref, &(if_cond), &(if_then), &(if_else), &(lex_cur)))) {
          (void)(((out->ok) = 0));
          return;
        }
        /* dest wrap IF dest: MATCH extra-arm last dest is IF dest.
         * TOKEN_MATCH last dest is already final_expr; TOKEN_IF
         * always appended if-stmt (dest-in-rbx CG002, host-C void).
         * G.7: last dest (kind 85 RBRACE or 95 `;` then 85) reuses
         * parse_if_expr_into (same as `*p = if`). Mid-block if-stmt
         * stays if-stmt. parse_if_expr_into fail falls back.
         * PLATFORM: SHARED dest wrap IF dest. Do not assemble parser.x. */
        (void)((rpeek_fe = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 }));
        (void)(lexer_next_into(&(rpeek_fe), lex_cur, source));
        if ((((rpeek_fe.tok).kind) ==95)) {
          struct lexer_LexerResult rpeek_if2 = (struct lexer_LexerResult){ .next_lex = (rpeek_fe.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
          (void)(lexer_next_into(&(rpeek_if2), (rpeek_fe.next_lex), source));
          if ((((rpeek_if2.tok).kind) ==85)) {
            (void)((rpeek_fe = rpeek_if2));
          }
        }
        if ((((rpeek_fe.tok).kind) ==85)) {
          /*
           * Final-position if: convert the ALREADY parsed if-STMT triple into
           * an EXPR_IF (parser_if_stmt_parts_to_if_expr) instead of re-parsing
           * the whole chain via parser_parse_if_expr_into. The old re-parse
           * doubled work per nesting level (2^N on deep else-chains; 29-deep
           * pipeline_asm_emit_expr_elf_rec hit 22-40GB RSS and jetsam). Zero
           * re-parse keeps block-final-if linear; conversion mirrors the
           * expr-path shape (G.7 same rule). Fallback to stmt only on
           * alloc failure. PLATFORM: SHARED.
           */
          int32_t if_expr_ref_c = parser_if_stmt_parts_to_if_expr(arena, if_cond, if_then, if_else, type_ref);
          if ((if_expr_ref_c !=0)) {
            /* Stale-b rollback guard: mid-body let runs append stmt_order after the
             * last b refresh; writing the stale snapshot back would rewind
             * num_stmt_order and drop those entries (host-C pre-let hoist then
             * uses names before their C declaration). Refresh b so only
             * final_expr_ref changes on a fresh snapshot. Same class applies to
             * every break-final writeback in this loop.
             * PLATFORM: SHARED. */
            (void)((b = ast_ast_arena_block_get(arena, block_ref)));
            (void)(((b.final_expr_ref) = (if_expr_ref_c)));
            (void)(ast_ast_arena_block_set(arena, block_ref, b));
            (void)((r = rpeek_fe));
            break;
          }
        }
        int32_t if_pool_i = pipeline_block_append_if(arena, block_ref, if_cond, if_then, if_else);
        if ((if_pool_i < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 5, if_pool_i) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((stmt_tok_ready = 0));
        continue;
      }
      if ((((r.tok).kind) ==84)) {
        /* dest extra-arm `{ fields }`: IDENT then :/,/} is STRUCT_LIT, not nested block.
         * G.7 twin of parser.x parse_block LBRACE peek + primary lbrace_looks_like_block.
         * PLATFORM: SHARED. Do not full-assemble parser.x (generic_bound_scan). */
        struct lexer_LexerResult rpeek_sl = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
        struct lexer_LexerResult rpeek_sl2 = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
        int32_t slit_stmt = 0;
        (void)(lexer_next_into(&(rpeek_sl), (r.next_lex), source));
        if ((((rpeek_sl.tok).kind) ==59)) {
          (void)(lexer_next_into(&(rpeek_sl2), (rpeek_sl.next_lex), source));
          if ((((((rpeek_sl2.tok).kind) ==91) || (((rpeek_sl2.tok).kind) ==90)) || (((rpeek_sl2.tok).kind) ==85))) {
            (void)((slit_stmt = 1));
          }
        }
        if ((slit_stmt ==0)) {
        struct parser_ParseBlockResult block_res_bare = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur };
        int32_t bare_expr = 0;
        int32_t bare_ex_i = 0;
        (void)(parser_lex_from_next_into(&(lex_cur), r));
        (void)((block_res_bare = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex_cur }));
        (void)(parser_parse_block_into(arena, lex_cur, source, type_ref, &(block_res_bare)));
        if (!((block_res_bare.ok))) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((bare_expr = parser_wrap_block_ref_as_expr(arena, (block_res_bare.block_ref), type_ref)));
        if ((bare_expr ==0)) {
          (void)(((out->ok) = 0));
          return;
        }
        /* dest extra-arm extra wrap `{ { let t; dest } }`: last nested
         * block is the dest value. Used to always append expr_stmt, so
         * host-C GNU stmt-expr was (void)({...}) assigned to dest.
         * dest-in-rbx peels BLOCK so asm was accidental green.
         * Peek: RBRACE or `;` then RBRACE → final_expr (same as STRUCT_LIT).
         * Mid-block `{ let ... } next_stmt` stays expr_stmt.
         * PLATFORM: SHARED. Do not assemble parser.x. */
        (void)((lex_cur = (block_res_bare.next_lex)));
        (void)((rpeek_fe = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 }));
        (void)(lexer_next_into(&(rpeek_fe), lex_cur, source));
        if ((((rpeek_fe.tok).kind) ==85)) {
          /* Stale-b rollback guard: refresh before final_expr writeback (see if-final note). */
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
          (void)(((b.final_expr_ref) = bare_expr));
          (void)(ast_ast_arena_block_set(arena, block_ref, b));
          (void)((r = rpeek_fe));
          break;
        }
        if ((((rpeek_fe.tok).kind) ==95)) {
          struct lexer_LexerResult rpeek_fe2 = (struct lexer_LexerResult){ .next_lex = (rpeek_fe.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
          (void)(lexer_next_into(&(rpeek_fe2), (rpeek_fe.next_lex), source));
          if ((((rpeek_fe2.tok).kind) ==85)) {
            /* Stale-b rollback guard: refresh before final_expr writeback (see if-final note). */
            (void)((b = ast_ast_arena_block_get(arena, block_ref)));
            (void)(((b.final_expr_ref) = bare_expr));
            (void)(ast_ast_arena_block_set(arena, block_ref, b));
            (void)((r = rpeek_fe2));
            break;
          }
        }
        (void)((bare_ex_i = pipeline_block_append_expr_stmt(arena, block_ref, bare_expr)));
        if ((bare_ex_i < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        if ((pipeline_block_append_stmt_order(arena, block_ref, 2, bare_ex_i) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)((stmt_tok_ready = 0));
        continue;
        }
      }
      (void)((stmt_start = parser_lex_at_token_from_result(r)));
      (void)(parser_parse_expr_result_reset(&(expr_stmt_res), stmt_start));
      (void)(parser_parse_expr_into(arena, stmt_start, source, &(expr_stmt_res)));
      if (!((expr_stmt_res.ok))) {
        (void)(((out->ok) = 0));
        return;
      }
      (void)((lex_cur = (expr_stmt_res.next_lex)));
      (void)((rpeek_fe = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 }));
      (void)(lexer_next_into(&(rpeek_fe), lex_cur, source));
      if ((((rpeek_fe.tok).kind) ==85)) {
        /* Stale-b rollback guard: refresh before final_expr writeback (see if-final note). */
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)(((b.final_expr_ref) = (expr_stmt_res.expr_ref)));
        (void)(ast_ast_arena_block_set(arena, block_ref, b));
        (void)((r = rpeek_fe));
        break;
      }
      if ((parser_advance_past_stmt_semicolon_into(&(r), lex_cur, source) ==0)) {
        if ((((r.tok).kind) ==85)) {
          /* Stale-b rollback guard: refresh before final_expr writeback (see if-final note). */
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
          (void)(((b.final_expr_ref) = (expr_stmt_res.expr_ref)));
          (void)(ast_ast_arena_block_set(arena, block_ref, b));
          break;
        }
        (void)(((out->ok) = 0));
        return;
      }
      if ((((r.tok).kind) ==85)) {
        /* Stale-b rollback guard: refresh before final_expr writeback (see if-final note). */
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        (void)(((b.final_expr_ref) = (expr_stmt_res.expr_ref)));
        (void)(ast_ast_arena_block_set(arena, block_ref, b));
        break;
      }
      if ((((r.tok).kind) ==95)) {
        (void)(parser_lex_from_result_ptr_into(&(lex_cur), &(r)));
        struct lexer_LexerResult after_semi_blk = (struct lexer_LexerResult){ .next_lex = lex_cur, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
        (void)(lexer_next_into(&(after_semi_blk), lex_cur, source));
        (void)((r = after_semi_blk));
      }
      (void)((ex_pool_i = pipeline_block_append_expr_stmt(arena, block_ref, (expr_stmt_res.expr_ref))));
      if ((ex_pool_i < 0)) {
        (void)(((out->ok) = 0));
        return;
      }
      if ((pipeline_block_append_stmt_order(arena, block_ref, 2, ex_pool_i) < 0)) {
        (void)(((out->ok) = 0));
        return;
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)((stmt_tok_ready = 1));
      continue;
    }
    (void)((b = ast_ast_arena_block_get(arena, block_ref)));
    if ((((b.num_lets) > 0) && ((b.num_stmt_order) ==0))) {
      int32_t li_fix = 0;
      while ((li_fix < (b.num_lets))) {
        if ((pipeline_block_append_stmt_order(arena, block_ref, 1, li_fix) < 0)) {
          (void)(((out->ok) = 0));
          return;
        }
        (void)((li_fix = (li_fix + 1)));
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
    }
    /* Stage12.0.5: persist early-let count for region fix_prefix (not num_lets). */
    (void)((b = ast_ast_arena_block_get(arena, block_ref)));
    (void)(((b.num_early_lets) = block_prefix_lets));
    (void)(ast_ast_arena_block_set(arena, block_ref, b));
    if ((block_prefix_lets > 0)) {
      (void)(pipeline_block_stmt_order_fix_prefix_lets(arena, block_ref, block_prefix_lets));
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
    }
    (void)(ast_ast_arena_block_set(arena, block_ref, b));
    (void)(((out->ok) = 1));
    (void)(((out->block_ref) = block_ref));
    (void)(((out->next_lex) = (r.next_lex)));
  }
}
int32_t parser_wrap_block_ref_as_expr(struct ast_ASTArena * arena, int32_t block_ref, int32_t type_ref) {
  {
    if ((block_ref ==0)) {
      return 0;
    }
    int32_t ref = ast_ast_arena_expr_alloc(arena);
    if ((ref ==0)) {
      return 0;
    }
    struct ast_Expr e = ast_ast_arena_expr_get(arena, ref);
    (void)(parser_expr_set_common_zeros(&(e)));
    (void)(((e.kind) = 26));
    (void)(((e.block_ref) = block_ref));
    (void)(((e.resolved_type_ref) = type_ref));
    (void)(((e.line) = 0));
    (void)(((e.col) = 0));
    (void)(ast_ast_arena_expr_set(arena, ref, e));
    return ref;
  }
}
extern void parser_parse_if_expr_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseExprResult * out);
void parser_parse_if_expr_into(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, struct xlang_slice_uint8_t * source, int32_t type_ref, struct parser_ParseExprResult * out) {
  (void)(parser_parse_if_expr_into_glue(arena, lex_at_if, source, type_ref, out));
}
/*
 * Convert an already-parsed if-STMT triple (cond expr + then/else block refs,
 * exactly what parser_parse_if_stmt_into returned) into an EXPR_IF node with
 * zero re-parsing. ROOT FIX for the exponential block-final-if blowup: the
 * old final-if path ran the full stmt parse and then a FULL re-parse via
 * parser_parse_if_expr_into, doubling work and arena garbage per nesting
 * level (2^N on deep else-chains; 29-deep pipeline_asm_emit_expr_elf_rec hit
 * 22-40GB RSS and jetsam-killed dev boxes). Mirrors the expr-path shape
 * (G.7 same rule): then/else wrapped as EXPR_BLOCK; implicit elif wraps
 * (single if-STMT, final_expr_ref==0) unrolled recursively so the EXPR_IF
 * chain shape matches the old re-parse output; missing else keeps 0.
 * Returns EXPR_IF ref or 0 on alloc failure (caller falls back to stmt).
 * PLATFORM: SHARED.
 */
static int32_t parser_if_stmt_parts_to_if_expr(struct ast_ASTArena * arena, int32_t cond_ref, int32_t then_blk, int32_t else_blk, int32_t type_ref) {
  int32_t then_expr_ref = parser_wrap_block_ref_as_expr(arena, then_blk, type_ref);
  if ((then_expr_ref ==0)) {
    return 0;
  }
  int32_t else_expr_ref = 0;
  if ((else_blk !=0)) {
    struct ast_Block eb = ast_ast_arena_block_get(arena, else_blk);
    if ((eb.final_expr_ref !=0)) {
      /* Real else-block whose own parse already converted its inner final if. */
      else_expr_ref = parser_wrap_block_ref_as_expr(arena, else_blk, type_ref);
    } else {
      if (((eb.num_if_stmts ==1) && (eb.num_stmt_order ==1))) {
        /* Implicit elif wrap: single if-STMT; recurse to a direct EXPR_IF chain. */
        int32_t ncond = ast_ast_block_if_cond_ref(arena, else_blk, 0);
        int32_t nthen = ast_ast_block_if_then_body_ref(arena, else_blk, 0);
        int32_t nelse = ast_ast_block_if_else_body_ref(arena, else_blk, 0);
        else_expr_ref = parser_if_stmt_parts_to_if_expr(arena, ncond, nthen, nelse, type_ref);
      } else {
        else_expr_ref = parser_wrap_block_ref_as_expr(arena, else_blk, type_ref);
      }
    }
    if ((else_expr_ref ==0)) {
      return 0;
    }
  }
  int32_t if_ref = ast_ast_arena_expr_alloc(arena);
  if ((if_ref ==0)) {
    return 0;
  }
  struct ast_Expr ie = ast_ast_arena_expr_get(arena, if_ref);
  (void)(parser_expr_set_common_zeros(&(ie)));
  (void)(((ie.kind) = 25)); /* EXPR_IF */
  (void)(((ie.resolved_type_ref) = type_ref));
  (void)(((ie.line) = 0));
  (void)(((ie.col) = 0));
  (void)(((ie.if_cond_ref) = cond_ref));
  (void)(((ie.if_then_ref) = then_expr_ref));
  (void)(((ie.if_else_ref) = else_expr_ref));
  (void)(ast_ast_arena_expr_set(arena, if_ref, ie));
  return if_ref;
}
struct parser_ParseResult parser_parse(struct xlang_slice_uint8_t * source) {
  {
    size_t arena_heap_bytes = pipeline_sizeof_arena();
    struct lexer_Lexer lex = lexer_init();
    struct lexer_LexerResult r = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=1)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=59)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=82)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=83)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=91)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=60)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=84)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=11)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    struct lexer_Lexer lex_at_expr_start = lex;
    (void)(lexer_next_into(&(r), lex, source));
    int32_t ret_val = 0;
    if ((((r.tok).kind) ==80)) {
      (void)((ret_val = ((r.tok).int_val)));
      (void)(parser_lex_from_next_into(&(lex), r));
    } else {
      uint8_t * raw_arena = calloc(1, arena_heap_bytes);
      if ((raw_arena ==((uint8_t *)(0)))) {
        return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
      }
      struct ast_ASTArena * heap_arena = ((struct ast_ASTArena *)(raw_arena));
      (void)(ast_ast_arena_init(heap_arena));
      struct parser_ParseExprResult expr_out = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
      (void)(parser_parse_expr_into(heap_arena, lex_at_expr_start, source, &(expr_out)));
      if ((!((expr_out.ok)) || ((expr_out.expr_ref) <=0))) {
        (void)(free(raw_arena));
        return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
      }
      struct ast_Expr e_read = ast_ast_arena_expr_get(heap_arena, (expr_out.expr_ref));
      if (((e_read.const_folded_valid) !=0)) {
        (void)((ret_val = (e_read.const_folded_val)));
      }
      (void)((lex = (expr_out.next_lex)));
      (void)(free(raw_arena));
    }
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=95)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=85)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=0)) {
      return (struct parser_ParseResult){ .ok = 0, .return_val = 0 };
    }
    return (struct parser_ParseResult){ .ok = 1, .return_val = ret_val };
  }
}
extern int32_t parser_first_token_kind_glue(struct xlang_slice_uint8_t * source);
int32_t parser_first_token_kind(struct xlang_slice_uint8_t * source) {
  return parser_first_token_kind_glue(source);
  return 0;
}
int32_t parser_first_token_kind_buf(uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_first_token_kind(&(slice));
  }
  return 0;
}
extern int32_t parser_diag_first_ident_len_glue(struct xlang_slice_uint8_t * source);
int32_t parser_diag_first_ident_len(struct xlang_slice_uint8_t * source) {
  return parser_diag_first_ident_len_glue(source);
  return 0;
}
int32_t parser_diag_first_ident_len_buf(uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_diag_first_ident_len(&(slice));
  }
  return 0;
}
extern void parser_diag_skip_let_const_into_glue(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_diag_skip_let_const_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_diag_skip_let_const_into_glue(out, lex, source));
}
extern struct lexer_LexerResult parser_diag_skip_let_const_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_LexerResult parser_diag_skip_let_const(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_diag_skip_let_const_glue(lex, source);
}
struct lexer_LexerResult parser_diag_skip_let_const_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_diag_skip_let_const(lex, &(slice));
  }
}
void parser_diag_skip_let_const_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_diag_skip_let_const_into(out, lex, &(slice)));
  }
}
extern void parser_body_skip_let_const_then_if_into_glue(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_body_skip_let_const_then_if_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_body_skip_let_const_then_if_into_glue(out, lex, source));
}
extern int32_t parser_parse_body_let_bracket_compound_init_ref_glue(struct ast_ASTArena * arena, size_t bracket_start, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out, struct lexer_LexerResult * r_out);
int32_t parser_parse_body_let_bracket_compound_init_ref(struct ast_ASTArena * arena, size_t bracket_start, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out, struct lexer_LexerResult * r_out) {
  return parser_parse_body_let_bracket_compound_init_ref_glue(arena, bracket_start, lex, source, lex_out, r_out);
  return 0;
}
extern int32_t parser_parse_type_ref_for_arena_into_glue(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex);
int32_t parser_parse_type_ref_for_arena_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex) {
  return parser_parse_type_ref_for_arena_into_glue(arena, lex, source, out_lex);
  return 0;
}
int parser_parse_body_lets_into(struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_OneFuncResult * out, struct lexer_Lexer * lex_out) {
  {
    uint8_t * pool = parser_onefunc_result_pool_ptr(out);
    struct lexer_LexerResult r = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    struct parser_ParseExprResult expr_tmp = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
    (void)(lexer_next_into(&(r), lex, source));
    if (((((r.tok).kind) !=2) && (((r.tok).kind) !=3))) {
      (void)((lex = parser_lex_at_token_from_result(r)));
      (void)(((lex_out->pos) = (lex.pos)));
      (void)(((lex_out->line) = (lex.line)));
      (void)(((lex_out->col) = (lex.col)));
      return 1;
    }
    while ((1 ==1)) {
      if (((((r.tok).kind) !=2) && (((r.tok).kind) !=3))) {
        break;
      }
      int is_let = (((r.tok).kind) ==2);
      int32_t let_init_val = 0;
      int32_t let_init_ref = 0;
      int32_t let_ty_ref = 0;
      int32_t is_discard_name = 0;
      int32_t name_len = 0;
      size_t name_start = 0;
      uint8_t name_row[128] = {};
      int32_t ni = 0;
      int32_t zi = 0;
      (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
      (void)(lexer_next_into(&(r), lex, source));
      /* wave385: optional IDENT "mut" after let (TOKEN_LET=2). PLATFORM: SHARED G.7 twin of parser.x. */
      if ((is_let && ((((r.tok).kind) ==59) && (((r.tok).ident_len) ==3)))) {
        size_t mut_start = (r.token_start);
        uint8_t m0 = 0;
        uint8_t m1 = 0;
        uint8_t m2 = 0;
        if ((mut_start < (source->length))) {
          (void)((m0 = (source)->data[mut_start]));
        }
        if (((mut_start + 1) < (source->length))) {
          (void)((m1 = (source)->data[(mut_start + 1)]));
        }
        if (((mut_start + 2) < (source->length))) {
          (void)((m2 = (source)->data[(mut_start + 2)]));
        }
        if ((((m0 ==109) && (m1 ==117)) && (m2 ==116))) {
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
        }
      }
      if ((((r.tok).kind) ==52)) {
        (void)((is_discard_name = 1));
      } else {
        /* 59=IDENT, 51=SELF: let self is a valid binding (TOKEN_SELF keyword spelling).
         * Other keywords (57=RUN unary, spawn/async/await, if, …) are not binding
         * names — soft return-0 dropped the function (P001). G.7: P014 hard.
         * Twin: parser.x parse_body_lets_into. PLATFORM: SHARED parse. */
        if (((((r.tok).kind) !=59) && (((r.tok).kind) !=51))) {
          {
            extern void parser_report_keyword_binding_p014_c(int32_t line, int32_t col);
            parser_report_keyword_binding_p014_c((int32_t)((r.tok).line), (int32_t)((r.tok).col));
          }
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
      }
      (void)((name_len = ((r.tok).ident_len)));
      if ((is_discard_name !=0)) {
        (void)((name_len = 1));
      } else {
        if ((((r.tok).kind) ==51)) {
          (void)((name_len = 4));
        }
      }
      if (((name_len <=0) || (name_len > 127))) {
        (void)(((lex_out->pos) = (lex.pos)));
        (void)(((lex_out->line) = (lex.line)));
        (void)(((lex_out->col) = (lex.col)));
        return 0;
      }
      (void)((name_start = (r.token_start)));
      if ((is_discard_name !=0)) {
        (void)(((name_row)[0] = 95));
        (void)((ni = 1));
      } else {
        while (((ni < name_len) && (ni < 128))) {
          if (((name_start + ni) < (source->length))) {
            (void)(((name_row)[ni] = (source)->data[(name_start + ni)]));
          }
          (void)((ni = (ni + 1)));
        }
      }
      (void)((zi = ni));
      while ((zi < 128)) {
        (void)(((name_row)[zi] = 0));
        (void)((zi = (zi + 1)));
      }
      if (is_let) {
      }
      (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
      (void)(lexer_next_into(&(r), lex, source));
      /* wave422/423: let requires `: Type`; const may omit type when next is `=`
       * (type_ref=0 → typeck infers from init). G.7 twin of parser.x.
       * PLATFORM: SHARED parse. kind 91=COLON, 117=ASSIGN. */
      if ((((r.tok).kind) ==91)) {
        (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
        (void)((let_ty_ref = parser_parse_type_ref_for_arena_into(arena, lex, source, &(lex))));
        if ((let_ty_ref ==0)) {
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
        (void)(lexer_next_into(&(r), lex, source));
      } else if ((!(is_let) && (((r.tok).kind) ==117))) {
        /* const name = init — wave423 type inference; leave let_ty_ref=0. */
        (void)((let_ty_ref = 0));
      } else {
        {
          extern void parser_report_untyped_binding_p010_c(int32_t line, int32_t col, int32_t is_let);
          parser_report_untyped_binding_p010_c((int32_t)((r.tok).line), (int32_t)((r.tok).col),
                                               is_let ? 1 : 0);
        }
        (void)(((lex_out->pos) = (lex.pos)));
        (void)(((lex_out->line) = (lex.line)));
        (void)(((lex_out->col) = (lex.col)));
        return 0;
      }
      int let_omit_init = 0;
      if ((((r.tok).kind) !=117)) {
        if (!(is_let)) {
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
        if (((((((((((r.tok).kind) !=95) && (((r.tok).kind) !=2)) && (((r.tok).kind) !=3)) && (((r.tok).kind) !=11)) && (((r.tok).kind) !=4)) && (((r.tok).kind) !=6)) && (((r.tok).kind) !=8)) && (((r.tok).kind) !=85))) {
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
        (void)((let_omit_init = 1));
        (void)((let_init_ref = -(1)));
        (void)((let_init_val = 0));
      } else {
        (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
        (void)(lexer_next_into(&(r), lex, source));
        (void)((let_init_ref = 0));
        (void)((let_init_val = 0));
      }
      int cast_init_semi_done = 0;
      int32_t init_handled = 0;
      if ((!(let_omit_init) && (((r.tok).kind) ==86))) {
        size_t bracket_start = (r.token_start);
        if ((bracket_start ==0)) {
          (void)((bracket_start = (lex.pos)));
        }
        (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
        (void)(lexer_next_into(&(r), lex, source));
        int32_t arr_ref = ast_ast_arena_expr_alloc(arena);
        if ((arr_ref !=0)) {
          struct ast_Expr ae0 = ast_ast_arena_expr_get(arena, arr_ref);
          (void)(((ae0.kind) = 46));
          (void)(((ae0.resolved_type_ref) = 0));
          (void)(((ae0.line) = 0));
          (void)(((ae0.col) = 0));
          (void)(parser_expr_set_common_zeros(&(ae0)));
          (void)(ast_ast_arena_expr_set(arena, arr_ref, ae0));
          while ((((r.tok).kind) !=87)) {
            if ((((r.tok).kind) ==80)) {
              int32_t er = ast_ast_arena_expr_alloc(arena);
              if ((er !=0)) {
                struct ast_Expr ee = ast_ast_arena_expr_get(arena, er);
                (void)(((ee.kind) = 0));
                (void)(((ee.resolved_type_ref) = 0));
                (void)(((ee.line) = 0));
                (void)(((ee.col) = 0));
                (void)(((ee.int_val) = ((r.tok).int_val)));
                (void)(parser_expr_set_common_zeros(&(ee)));
                (void)(ast_ast_arena_expr_set(arena, er, ee));
                (void)(pipeline_expr_append_array_lit_elem(arena, arr_ref, er));
              }
              (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
              (void)(lexer_next_into(&(r), lex, source));
            } else {
              if ((((r.tok).kind) ==81)) {
                int32_t er = parser_alloc_float_lit(arena, ((r.tok).float_val));
                if ((er !=0)) {
                  (void)(pipeline_expr_append_array_lit_elem(arena, arr_ref, er));
                }
                (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
                (void)(lexer_next_into(&(r), lex, source));
              } else {
                if ((((r.tok).kind) ==90)) {
                  (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) ==87)) {
                    break;
                  }
                } else {
                  if ((((r.tok).kind) ==87)) {
                    break;
                  } else {
                    break;
                  }
                }
              }
            }
          }
          if ((((r.tok).kind) ==87)) {
            (void)((let_init_ref = arr_ref));
            (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
            (void)(lexer_next_into(&(r), lex, source));
          }
        }
        int arr_init_plain = ((((((((((r.tok).kind) ==95) || (((r.tok).kind) ==2)) || (((r.tok).kind) ==3)) || (((r.tok).kind) ==11)) || (((r.tok).kind) ==4)) || (((r.tok).kind) ==6)) || (((r.tok).kind) ==8)) || (((r.tok).kind) ==85));
        /* PLATFORM: SHARED — body const nested [..] / as: same compound
         * reparse as let. is_let gate dropped the whole function (P001).
         * Twin: parser.x parse_body_lets_into. Do not full-reassemble
         * parser.x (tip -E drops generic_bound_scan). */
        if (((((r.tok).kind) ==128) || !(arr_init_plain))) {
          int32_t reparsed_ref = parser_parse_body_let_bracket_compound_init_ref(arena, bracket_start, lex, source, &(lex), &(r));
          if ((reparsed_ref ==0)) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = reparsed_ref));
        }
        (void)((init_handled = 1));
      }
      /*
       * wave474 Cap residual pure: TOKEN_SELF (51) let-init same as IDENT (59).
       * `let x: i32 = self.v` — primary already accepts TOKEN_SELF as EXPR_VAR;
       * body_lets must route here so init_handled is set. G.7 twin of parser.x.
       * PLATFORM: SHARED parse.
       */
      if ((init_handled ==0)) {
        /* 59=IDENT, 51=SELF, 129=TOKEN_AT (@shuffle/@select body-let init). G.7 ≡ parser.x. */
        if (((((r.tok).kind) ==59) || (((r.tok).kind) ==51) || (((r.tok).kind) ==129))) {
          size_t rhs_ident_start = (r.token_start);
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          struct lexer_Lexer expr_lex = (struct lexer_Lexer){ .pos = rhs_ident_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_parse_expr_result_reset(&(expr_tmp), expr_lex));
          (void)(parser_parse_expr_into(arena, expr_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)(parser_rewind_lex_for_following_stmt_into(&(lex), lex, r));
          (void)((init_handled = 1));
        }
      }
      /*
       * wave375 / C3=C4: LBRACE let-init (TOKEN_LBRACE=84).
       * PLATFORM: SHARED — G.7 twin of parser.x parse_body_lets_into LBRACE branch.
       * Seed historically jumped IDENT(59) → STRING(130) and dropped bare `{ ... }` inits
       * (block expr `{ 42 }` and anonymous struct lit `{ fd: 1 }`). Primary already
       * disambiguates via parser_asm_primary_lbrace_looks_like_block_c; only missing
       * is reaching parse_expr_into from the `{` start (same as IDENT path).
       */
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==84)) {
          size_t lbrace_start = (r.token_start);
          if ((lbrace_start ==0)) {
            (void)((lbrace_start = (lex.pos)));
          }
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          struct lexer_Lexer lbrace_lex = (struct lexer_Lexer){ .pos = lbrace_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_parse_expr_result_reset(&(expr_tmp), lbrace_lex));
          (void)(parser_parse_expr_into(arena, lbrace_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)(parser_rewind_lex_for_following_stmt_into(&(lex), lex, r));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==130)) {
          int32_t str_ref = ast_ast_arena_expr_alloc(arena);
          if ((str_ref !=0)) {
            struct ast_Expr se = ast_ast_arena_expr_get(arena, str_ref);
            (void)(((se.kind) = 59));
            (void)(((se.resolved_type_ref) = 0));
            (void)(((se.line) = ((r.tok).line)));
            (void)(((se.col) = ((r.tok).col)));
            (void)(parser_expr_set_common_zeros(&(se)));
            int32_t nlen = ((r.tok).ident_len);
            /* wave283: full span; L011 on overflow (not silent truncate).
             * wave1222: cap 63→127 to match Expr.var_name[128] capacity. */
            if ((nlen < 0)) {
              (void)((nlen = 0));
            }
            size_t q0 = (r.token_start);
            int32_t ri = 0;
            int32_t wi = 0;
            while ((ri < nlen)) {
              if ((wi >= 127)) {
                lexer_note_string_lit_overflow((se.line), (se.col));
                break;
              }
              uint8_t c = 0;
              if (((q0 + ((size_t)(ri))) < (source->length))) {
                (void)((c = (source)->data[(q0 + ((size_t)(ri)))]));
              }
              if (((c ==92) && ((ri + 1) < nlen))) {
                uint8_t n = 0;
                if (((q0 + ((size_t)((ri + 1)))) < (source->length))) {
                  (void)((n = (source)->data[(q0 + ((size_t)((ri + 1))))]));
                }
                if ((n ==110)) {
                  (void)((((se.var_name))[wi] = 10));
                  (void)((wi = (wi + 1)));
                  (void)((ri = (ri + 2)));
                  continue;
                }
                if ((n ==116)) {
                  (void)((((se.var_name))[wi] = 9));
                  (void)((wi = (wi + 1)));
                  (void)((ri = (ri + 2)));
                  continue;
                }
                if ((n ==114)) {
                  (void)((((se.var_name))[wi] = 13));
                  (void)((wi = (wi + 1)));
                  (void)((ri = (ri + 2)));
                  continue;
                }
                if ((n ==48)) {
                  (void)((((se.var_name))[wi] = 0));
                  (void)((wi = (wi + 1)));
                  (void)((ri = (ri + 2)));
                  continue;
                }
                if (((n ==92) || (n ==34))) {
                  (void)((((se.var_name))[wi] = n));
                  (void)((wi = (wi + 1)));
                  (void)((ri = (ri + 2)));
                  continue;
                }
                /* wave281: \xHH → one semantic byte (G.7 ≡ parser.x / primary_slice). */
                if (((n ==120) && ((ri + 3) < nlen))) {
                  uint8_t h1 = 0;
                  uint8_t h2 = 0;
                  int32_t v1 = -1;
                  int32_t v2 = -1;
                  if (((q0 + ((size_t)((ri + 2)))) < (source->length))) {
                    (void)((h1 = (source)->data[(q0 + ((size_t)((ri + 2))))]));
                  }
                  if (((q0 + ((size_t)((ri + 3)))) < (source->length))) {
                    (void)((h2 = (source)->data[(q0 + ((size_t)((ri + 3))))]));
                  }
                  if (((h1 >= 48) && (h1 <= 57))) {
                    (void)((v1 = (((int32_t)(h1)) - 48)));
                  }
                  if (((h1 >= 97) && (h1 <= 102))) {
                    (void)((v1 = ((((int32_t)(h1)) - 97) + 10)));
                  }
                  if (((h1 >= 65) && (h1 <= 70))) {
                    (void)((v1 = ((((int32_t)(h1)) - 65) + 10)));
                  }
                  if (((h2 >= 48) && (h2 <= 57))) {
                    (void)((v2 = (((int32_t)(h2)) - 48)));
                  }
                  if (((h2 >= 97) && (h2 <= 102))) {
                    (void)((v2 = ((((int32_t)(h2)) - 97) + 10)));
                  }
                  if (((h2 >= 65) && (h2 <= 70))) {
                    (void)((v2 = ((((int32_t)(h2)) - 65) + 10)));
                  }
                  if (((v1 >= 0) && (v2 >= 0))) {
                    (void)((((se.var_name))[wi] = ((uint8_t)(((v1 * 16) + v2)))));
                    (void)((wi = (wi + 1)));
                    (void)((ri = (ri + 4)));
                    continue;
                  }
                }
                (void)((((se.var_name))[wi] = n));
                (void)((wi = (wi + 1)));
                (void)((ri = (ri + 2)));
                continue;
              }
              (void)((((se.var_name))[wi] = c));
              (void)((wi = (wi + 1)));
              (void)((ri = (ri + 1)));
            }
            (void)(((se.var_name_len) = wi));
            while ((wi < 128)) {
              (void)((((se.var_name))[wi] = 0));
              (void)((wi = (wi + 1)));
            }
            (void)(ast_ast_arena_expr_set(arena, str_ref, se));
            (void)((let_init_ref = str_ref));
          }
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
          /* wave282: C-style adjacent string-literal concat (G.7 ≡ parser.x / primary_slice).
           * Soft residual: 2nd+ TOKEN_STRING after let-init was bare expr-stmt and dropped. */
          while (((((r.tok).kind) ==130) && (str_ref !=0))) {
            struct ast_Expr se_adj = ast_ast_arena_expr_get(arena, str_ref);
            int32_t wi_adj = (se_adj.var_name_len);
            int32_t nlen_adj = ((r.tok).ident_len);
            size_t q0_adj = (r.token_start);
            int32_t ri_adj = 0;
            if ((wi_adj < 0)) {
              (void)((wi_adj = 0));
            }
            if ((wi_adj > 127)) {
              (void)((wi_adj = 127));
            }
            if ((nlen_adj < 0)) {
              (void)((nlen_adj = 0));
            }
            while ((ri_adj < nlen_adj)) {
              if ((wi_adj >= 127)) {
                lexer_note_string_lit_overflow((se_adj.line), (se_adj.col));
                break;
              }
              uint8_t c2 = 0;
              if (((q0_adj + ((size_t)(ri_adj))) < (source->length))) {
                (void)((c2 = (source)->data[(q0_adj + ((size_t)(ri_adj)))]));
              }
              if (((c2 ==92) && ((ri_adj + 1) < nlen_adj))) {
                uint8_t n2 = 0;
                if (((q0_adj + ((size_t)((ri_adj + 1)))) < (source->length))) {
                  (void)((n2 = (source)->data[(q0_adj + ((size_t)((ri_adj + 1))))]));
                }
                if ((n2 ==110)) {
                  (void)((((se_adj.var_name))[wi_adj] = 10));
                  (void)((wi_adj = (wi_adj + 1)));
                  (void)((ri_adj = (ri_adj + 2)));
                  continue;
                }
                if ((n2 ==116)) {
                  (void)((((se_adj.var_name))[wi_adj] = 9));
                  (void)((wi_adj = (wi_adj + 1)));
                  (void)((ri_adj = (ri_adj + 2)));
                  continue;
                }
                if ((n2 ==114)) {
                  (void)((((se_adj.var_name))[wi_adj] = 13));
                  (void)((wi_adj = (wi_adj + 1)));
                  (void)((ri_adj = (ri_adj + 2)));
                  continue;
                }
                if ((n2 ==48)) {
                  (void)((((se_adj.var_name))[wi_adj] = 0));
                  (void)((wi_adj = (wi_adj + 1)));
                  (void)((ri_adj = (ri_adj + 2)));
                  continue;
                }
                if (((n2 ==92) || (n2 ==34))) {
                  (void)((((se_adj.var_name))[wi_adj] = n2));
                  (void)((wi_adj = (wi_adj + 1)));
                  (void)((ri_adj = (ri_adj + 2)));
                  continue;
                }
                if (((n2 ==120) && ((ri_adj + 3) < nlen_adj))) {
                  uint8_t h1b = 0;
                  uint8_t h2b = 0;
                  int32_t v1b = -1;
                  int32_t v2b = -1;
                  if (((q0_adj + ((size_t)((ri_adj + 2)))) < (source->length))) {
                    (void)((h1b = (source)->data[(q0_adj + ((size_t)((ri_adj + 2))))]));
                  }
                  if (((q0_adj + ((size_t)((ri_adj + 3)))) < (source->length))) {
                    (void)((h2b = (source)->data[(q0_adj + ((size_t)((ri_adj + 3))))]));
                  }
                  if (((h1b >= 48) && (h1b <= 57))) {
                    (void)((v1b = (((int32_t)(h1b)) - 48)));
                  }
                  if (((h1b >= 97) && (h1b <= 102))) {
                    (void)((v1b = ((((int32_t)(h1b)) - 97) + 10)));
                  }
                  if (((h1b >= 65) && (h1b <= 70))) {
                    (void)((v1b = ((((int32_t)(h1b)) - 65) + 10)));
                  }
                  if (((h2b >= 48) && (h2b <= 57))) {
                    (void)((v2b = (((int32_t)(h2b)) - 48)));
                  }
                  if (((h2b >= 97) && (h2b <= 102))) {
                    (void)((v2b = ((((int32_t)(h2b)) - 97) + 10)));
                  }
                  if (((h2b >= 65) && (h2b <= 70))) {
                    (void)((v2b = ((((int32_t)(h2b)) - 65) + 10)));
                  }
                  if (((v1b >= 0) && (v2b >= 0))) {
                    (void)((((se_adj.var_name))[wi_adj] = ((uint8_t)(((v1b * 16) + v2b)))));
                    (void)((wi_adj = (wi_adj + 1)));
                    (void)((ri_adj = (ri_adj + 4)));
                    continue;
                  }
                }
                (void)((((se_adj.var_name))[wi_adj] = n2));
                (void)((wi_adj = (wi_adj + 1)));
                (void)((ri_adj = (ri_adj + 2)));
                continue;
              }
              (void)((((se_adj.var_name))[wi_adj] = c2));
              (void)((wi_adj = (wi_adj + 1)));
              (void)((ri_adj = (ri_adj + 1)));
            }
            (void)(((se_adj.var_name_len) = wi_adj));
            while ((wi_adj < 128)) {
              (void)((((se_adj.var_name))[wi_adj] = 0));
              (void)((wi_adj = (wi_adj + 1)));
            }
            (void)(ast_ast_arena_expr_set(arena, str_ref, se_adj));
            (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
            (void)(lexer_next_into(&(r), lex, source));
          }
          (void)(parser_rewind_lex_for_following_stmt_into(&(lex), lex, r));
          if ((((r.tok).kind) ==95)) {
            struct lexer_LexerResult after_semi_str = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
            (void)(lexer_next_into(&(after_semi_str), (r.next_lex), source));
            (void)(parser_lexer_copy_into(&(lex), parser_lex_at_token_from_result(after_semi_str)));
            (void)(lexer_next_into(&(r), lex, source));
            (void)((cast_init_semi_done = 1));
          }
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if (((((r.tok).kind) ==75) || (((r.tok).kind) ==76))) {
          int32_t bool_ref = ast_ast_arena_expr_alloc(arena);
          if ((bool_ref !=0)) {
            struct ast_Expr be = ast_ast_arena_expr_get(arena, bool_ref);
            (void)(((be.kind) = 2));
            (void)(((be.resolved_type_ref) = 0));
            (void)(((be.line) = 0));
            (void)(((be.col) = 0));
            (void)(((be.int_val) = 0));
            if ((((r.tok).kind) ==75)) {
              (void)(((be.int_val) = 1));
            }
            (void)(ast_expr_init_match_enum(&(be)));
            (void)(((be.binop_left_ref) = 0));
            (void)(((be.binop_right_ref) = 0));
            (void)(((be.unary_operand_ref) = 0));
            (void)(((be.if_cond_ref) = 0));
            (void)(((be.if_then_ref) = 0));
            (void)(((be.if_else_ref) = 0));
            (void)(((be.block_ref) = 0));
            (void)(((be.field_access_base_ref) = 0));
            (void)(((be.field_access_field_len) = 0));
            (void)(((be.field_access_is_enum_variant) = 0));
            (void)(((be.field_access_offset) = 0));
            (void)(((be.index_base_ref) = 0));
            (void)(((be.index_index_ref) = 0));
            (void)(((be.index_base_is_slice) = 0));
            (void)(((be.call_callee_ref) = 0));
            (void)(((be.call_num_args) = 0));
            (void)(((be.method_call_base_ref) = 0));
            (void)(((be.method_call_name_len) = 0));
            (void)(((be.method_call_num_args) = 0));
            (void)(((be.const_folded_val) = 0));
            (void)(((be.const_folded_valid) = 0));
            (void)(((be.index_proven_in_bounds) = 0));
            (void)(ast_ast_arena_expr_set(arena, bool_ref, be));
            (void)((let_init_ref = bool_ref));
          }
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)((init_handled = 1));
        }
      }
      /* wave668/wave670: let p:*T = null → EXPR_LIT 0 tagged var_name="null". */
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==132)) {
          (void)((let_init_ref = parser_alloc_int_lit(arena, 0)));
          if ((let_init_ref != 0)) {
            struct ast_Expr ne = ast_ast_arena_expr_get(arena, let_init_ref);
            int32_t zi;
            ne.var_name[0] = (uint8_t)'n';
            ne.var_name[1] = (uint8_t)'u';
            ne.var_name[2] = (uint8_t)'l';
            ne.var_name[3] = (uint8_t)'l';
            ne.var_name_len = 4;
            for (zi = 4; zi < 128; zi++)
              ne.var_name[zi] = 0;
            (void)(ast_ast_arena_expr_set(arena, let_init_ref, ne));
          }
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        /* G.7: FLOAT compound let-init mirrors TOKEN_INT (kind 80); bare lit keeps alloc_float_lit.
         * PLATFORM: SHARED — body/mid-block lets. */
        if ((((r.tok).kind) ==81)) {
          double float_val_saved = ((r.tok).float_val);
          size_t float_start = (r.token_start);
          if ((float_start ==0)) {
            (void)((float_start = (((r.next_lex).pos) - 1)));
          }
          struct lexer_Lexer float_lex = (struct lexer_Lexer){ .pos = float_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
          int float_init_plain = ((((((((((r.tok).kind) ==95) || (((r.tok).kind) ==2)) || (((r.tok).kind) ==3)) || (((r.tok).kind) ==11)) || (((r.tok).kind) ==4)) || (((r.tok).kind) ==6)) || (((r.tok).kind) ==8)) || (((r.tok).kind) ==85));
          if (((((r.tok).kind) ==128) || !(float_init_plain))) {
            (void)(parser_parse_expr_result_reset(&(expr_tmp), float_lex));
            (void)(parser_parse_expr_into(arena, float_lex, source, &(expr_tmp)));
            if (!((expr_tmp.ok))) {
              (void)(((lex_out->pos) = (lex.pos)));
              (void)(((lex_out->line) = (lex.line)));
              (void)(((lex_out->col) = (lex.col)));
              return 0;
            }
            (void)((let_init_ref = (expr_tmp.expr_ref)));
            (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
            (void)(lexer_next_into(&(r), lex, source));
          } else {
            (void)((let_init_ref = parser_alloc_float_lit(arena, float_val_saved)));
          }
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==80)) {
          /* wave305: full i64; plain let uses parser_alloc_int_lit (not i32 sidecar). */
          int64_t int_val_saved = ((r.tok).int_val);
          size_t int_start = (r.token_start);
          if ((int_start ==0)) {
            (void)((int_start = (((r.next_lex).pos) - 1)));
          }
          struct lexer_Lexer int_lex = (struct lexer_Lexer){ .pos = int_start, .line = (lex.line), .col = (lex.col) };
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(lexer_next_into(&(r), lex, source));
          int int_init_plain = ((((((((((r.tok).kind) ==95) || (((r.tok).kind) ==2)) || (((r.tok).kind) ==3)) || (((r.tok).kind) ==11)) || (((r.tok).kind) ==4)) || (((r.tok).kind) ==6)) || (((r.tok).kind) ==8)) || (((r.tok).kind) ==85));
          if (((((r.tok).kind) ==128) || !(int_init_plain))) {
            (void)(parser_parse_expr_result_reset(&(expr_tmp), int_lex));
            (void)(parser_parse_expr_into(arena, int_lex, source, &(expr_tmp)));
            if (!((expr_tmp.ok))) {
              (void)(((lex_out->pos) = (lex.pos)));
              (void)(((lex_out->line) = (lex.line)));
              (void)(((lex_out->col) = (lex.col)));
              return 0;
            }
            (void)((let_init_ref = (expr_tmp.expr_ref)));
            (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
            (void)(lexer_next_into(&(r), lex, source));
          } else {
            (void)((let_init_ref = parser_alloc_int_lit(arena, int_val_saved)));
            (void)((let_init_val = 0));
            if ((let_init_ref ==0)) {
              (void)(((lex_out->pos) = (lex.pos)));
              (void)(((lex_out->line) = (lex.line)));
              (void)(((lex_out->col) = (lex.col)));
              return 0;
            }
          }
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((((((r.tok).kind) ==97) || (((r.tok).kind) ==126)) || (((r.tok).kind) ==82)) || (((r.tok).kind) ==116)) || (((r.tok).kind) ==98))) {
          size_t rhs_unary_start = (r.token_start);
          if ((rhs_unary_start ==0)) {
            (void)((rhs_unary_start = (lex.pos)));
          }
          struct lexer_Lexer unary_lex = (struct lexer_Lexer){ .pos = rhs_unary_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(parser_parse_expr_result_reset(&(expr_tmp), unary_lex));
          (void)(parser_parse_expr_into(arena, unary_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==101)) {
          size_t amp_start = (r.token_start);
          if ((amp_start ==0)) {
            (void)((amp_start = (lex.pos)));
          }
          struct lexer_Lexer amp_lex = (struct lexer_Lexer){ .pos = amp_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(parser_parse_expr_result_reset(&(expr_tmp), amp_lex));
          (void)(parser_parse_expr_into(arena, amp_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==4)) {
          struct lexer_Lexer if_lex = parser_lex_at_token_from_result(r);
          (void)(parser_parse_expr_result_reset(&(expr_tmp), if_lex));
          (void)(parser_parse_if_expr_into(arena, if_lex, source, let_ty_ref, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)(parser_rewind_lex_for_following_stmt_into(&(lex), lex, r));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((r.tok).kind) ==18)) {
          struct lexer_Lexer match_lex = parser_lex_at_token_from_result(r);
          (void)(parser_parse_expr_result_reset(&(expr_tmp), match_lex));
          (void)(parser_parse_match_into(arena, match_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)(parser_rewind_lex_for_following_stmt_into(&(lex), lex, r));
          (void)((init_handled = 1));
        }
      }
      if ((init_handled ==0)) {
        if ((((((r.tok).kind) ==56) || (((r.tok).kind) ==57)) || (((r.tok).kind) ==58))) {
          size_t async_start = (r.token_start);
          if ((async_start ==0)) {
            (void)((async_start = (lex.pos)));
          }
          struct lexer_Lexer async_lex = (struct lexer_Lexer){ .pos = async_start, .line = ((r.tok).line), .col = ((r.tok).col) };
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          (void)(parser_parse_expr_result_reset(&(expr_tmp), async_lex));
          (void)(parser_parse_expr_into(arena, async_lex, source, &(expr_tmp)));
          if (!((expr_tmp.ok))) {
            (void)(((lex_out->pos) = (lex.pos)));
            (void)(((lex_out->line) = (lex.line)));
            (void)(((lex_out->col) = (lex.col)));
            return 0;
          }
          (void)((let_init_ref = (expr_tmp.expr_ref)));
          (void)(parser_lexer_copy_from_parse_expr_result_into(&(lex), &(expr_tmp)));
          (void)(lexer_next_into(&(r), lex, source));
          (void)((init_handled = 1));
        }
      }
      if (!(cast_init_semi_done)) {
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          struct lexer_LexerResult after_semi = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
          (void)(lexer_next_into(&(after_semi), lex, source));
          (void)(parser_lexer_copy_into(&(lex), parser_lex_at_token_from_result(after_semi)));
          (void)(lexer_next_into(&(r), lex, source));
        } else {
          if ((((((((((r.tok).kind) !=2) && (((r.tok).kind) !=3)) && (((r.tok).kind) !=11)) && (((r.tok).kind) !=4)) && (((r.tok).kind) !=6)) && (((r.tok).kind) !=8)) && (((r.tok).kind) !=85))) {
            if (is_let) {
              if (!((((let_init_ref !=0) || (let_init_val !=0)) || (let_init_ref ==-(1))))) {
                (void)(((lex_out->pos) = (lex.pos)));
                (void)(((lex_out->line) = (lex.line)));
                (void)(((lex_out->col) = (lex.col)));
                return 0;
              }
            } else {
              if (((let_init_ref ==0) && (let_init_val ==0))) {
                (void)(((lex_out->pos) = (lex.pos)));
                (void)(((lex_out->line) = (lex.line)));
                (void)(((lex_out->col) = (lex.col)));
                return 0;
              }
            }
            (void)(parser_lexer_copy_into(&(lex), parser_lex_at_token_from_result(r)));
          }
        }
      }
      if (is_let) {
        if ((pipeline_onefunc_append_let(pool, &((name_row)[0]), name_len, let_init_val, let_init_ref, let_ty_ref) < 0)) {
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
        (void)(((out->num_lets) = pipeline_onefunc_num_lets(pool)));
      } else {
        if ((pipeline_onefunc_append_const(pool, &((name_row)[0]), name_len, let_init_val, let_init_ref, let_ty_ref) < 0)) {
          (void)(((lex_out->pos) = (lex.pos)));
          (void)(((lex_out->line) = (lex.line)));
          (void)(((lex_out->col) = (lex.col)));
          return 0;
        }
        (void)(((out->num_consts) = pipeline_onefunc_num_consts(pool)));
      }
    }
    (void)(((lex_out->pos) = (lex.pos)));
    (void)(((lex_out->line) = (lex.line)));
    (void)(((lex_out->col) = (lex.col)));
    return 1;
  }
  return 0;
}
extern struct lexer_LexerResult parser_body_skip_let_const_then_if_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_LexerResult parser_body_skip_let_const_then_if(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_body_skip_let_const_then_if_glue(lex, source);
}
struct lexer_LexerResult parser_body_skip_let_const_then_if_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_body_skip_let_const_then_if(lex, &(slice));
  }
}
void parser_body_skip_let_const_then_if_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_body_skip_let_const_then_if_into(out, lex, &(slice)));
  }
}
extern struct lexer_Lexer parser_skip_balanced_parens_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_balanced_parens(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_balanced_parens_glue(lex, source);
}
extern void parser_skip_balanced_parens_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_balanced_parens_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_balanced_parens_into_glue(out, lex, source));
}
void parser_skip_balanced_parens_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    int32_t depth = 1;
    while ((depth > 0)) {
      struct lexer_LexerResult r = lexer_next_buf(lex, data, len);
      if ((((r.tok).kind) ==82)) {
        (void)((depth = (depth + 1)));
      } else {
        if ((((r.tok).kind) ==83)) {
          (void)((depth = (depth - 1)));
          if ((depth ==0)) {
            (void)(((out->pos) = ((r.next_lex).pos)));
            (void)(((out->line) = ((r.next_lex).line)));
            (void)(((out->col) = ((r.next_lex).col)));
            return;
          }
        }
      }
      if ((((r.tok).kind) ==0)) {
        (void)(((out->pos) = (lex.pos)));
        (void)(((out->line) = (lex.line)));
        (void)(((out->col) = (lex.col)));
        return;
      }
      (void)(parser_lex_from_next_into(&(lex), r));
    }
    (void)(((out->pos) = (lex.pos)));
    (void)(((out->line) = (lex.line)));
    (void)(((out->col) = (lex.col)));
  }
}
struct lexer_Lexer parser_skip_balanced_parens_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_balanced_parens(lex, &(slice));
  }
}
extern struct lexer_Lexer parser_skip_balanced_braces_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_balanced_braces(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_balanced_braces_glue(lex, source);
}
extern void parser_skip_balanced_braces_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_balanced_braces_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_balanced_braces_into_glue(out, lex, source));
}
void parser_skip_balanced_braces_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    int32_t depth = 1;
    while ((depth > 0)) {
      struct lexer_LexerResult r = lexer_next_buf(lex, data, len);
      if ((((r.tok).kind) ==84)) {
        (void)((depth = (depth + 1)));
      } else {
        if ((((r.tok).kind) ==85)) {
          (void)((depth = (depth - 1)));
          if ((depth ==0)) {
            (void)(((out->pos) = ((r.next_lex).pos)));
            (void)(((out->line) = ((r.next_lex).line)));
            (void)(((out->col) = ((r.next_lex).col)));
            return;
          }
        }
      }
      if ((((r.tok).kind) ==0)) {
        (void)(((out->pos) = (lex.pos)));
        (void)(((out->line) = (lex.line)));
        (void)(((out->col) = (lex.col)));
        return;
      }
      (void)(parser_lex_from_next_into(&(lex), r));
    }
    (void)(((out->pos) = (lex.pos)));
    (void)(((out->line) = (lex.line)));
    (void)(((out->col) = (lex.col)));
  }
}
struct lexer_Lexer parser_skip_balanced_braces_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_balanced_braces(lex, &(slice));
  }
}
extern void parser_skip_one_function_full_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_function_full_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_function_full_into_glue(out, lex, source));
}
extern void parser_skip_one_top_level_const_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_top_level_const_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_top_level_const_into_glue(out, lex, source));
}
extern void parser_skip_one_top_level_const_into_buf_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
void parser_skip_one_top_level_const_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  (void)(parser_skip_one_top_level_const_into_buf_glue(out, lex, data, len));
}
extern void parser_skip_one_top_level_let_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_top_level_let_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_top_level_let_into_glue(out, lex, source));
}
extern void parser_skip_one_top_level_let_into_buf_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len);
void parser_skip_one_top_level_let_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  (void)(parser_skip_one_top_level_let_into_buf_glue(out, lex, data, len));
}
extern struct lexer_Lexer parser_skip_one_function_full_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_function_full(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_function_full_glue(lex, source);
}
void parser_skip_one_function_full_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_function_full_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_function_full_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_function_full(lex, &(slice));
  }
}
extern struct lexer_LexerResult parser_skip_one_if_core_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_LexerResult parser_skip_one_if_core(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_if_core_glue(lex, source);
}
extern struct lexer_LexerResult parser_skip_one_if_statement_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_LexerResult parser_skip_one_if_statement(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_if_statement_glue(lex, source);
}
extern void parser_skip_one_if_statement_into_glue(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_if_statement_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_if_statement_into_glue(out, lex, source));
}
extern void parser_skip_one_if_core_into_glue(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_if_core_into(struct lexer_LexerResult * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_if_core_into_glue(out, lex, source));
}
struct lexer_LexerResult parser_skip_one_if_core_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_if_core(lex, &(slice));
  }
}
struct lexer_LexerResult parser_skip_one_if_statement_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_if_statement(lex, &(slice));
  }
}
void parser_skip_one_if_core_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_if_core_into(out, lex, &(slice)));
  }
}
void parser_skip_one_if_statement_into_buf(struct lexer_LexerResult * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_if_statement_into(out, lex, &(slice)));
  }
}
extern struct lexer_Lexer parser_diag_lex_after_imports_glue(struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_diag_lex_after_imports(struct xlang_slice_uint8_t * source) {
  return parser_diag_lex_after_imports_glue(source);
}
struct lexer_Lexer parser_diag_lex_after_imports_buf(uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_diag_lex_after_imports(&(slice));
  }
}
extern struct lexer_LexerResult parser_diag_after_imports_then_structs_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_LexerResult parser_diag_after_imports_then_structs(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_diag_after_imports_then_structs_glue(lex, source);
}
struct lexer_LexerResult parser_diag_after_imports_then_structs_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_diag_after_imports_then_structs(lex, &(slice));
  }
}
extern int32_t parser_diag_fail_at_token_kind_glue(struct xlang_slice_uint8_t * source);
int32_t parser_diag_fail_at_token_kind(struct xlang_slice_uint8_t * source) {
  return parser_diag_fail_at_token_kind_glue(source);
  return 0;
}
int32_t parser_diag_fail_at_token_kind_buf(uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_diag_fail_at_token_kind(&(slice));
  }
  return 0;
}
/* wave269: L001 unclosed block comment sticky pending (lexer.x).
 * wave271: L002 unclosed string literal sticky pending (lexer.x).
 * wave272: L003 illegal character sticky pending (lexer.x).
 * wave273: L004 incomplete hex sticky pending (lexer.x). */
extern void lexer_unclosed_block_comment_reset(void);
extern int32_t lexer_unclosed_block_comment_pending(void);
extern void lexer_unclosed_string_reset(void);
extern int32_t lexer_unclosed_string_pending(void);
extern void lexer_illegal_char_reset(void);
extern int32_t lexer_illegal_char_pending(void);
extern void lexer_incomplete_hex_reset(void);
extern int32_t lexer_incomplete_hex_pending(void);
extern void lexer_incomplete_exp_reset(void);
extern int32_t lexer_incomplete_exp_pending(void);
extern void lexer_incomplete_bin_reset(void);
extern int32_t lexer_incomplete_bin_pending(void);
extern void lexer_incomplete_oct_reset(void);
extern int32_t lexer_incomplete_oct_pending(void);
extern void lexer_invalid_digit_sep_reset(void);
extern int32_t lexer_invalid_digit_sep_pending(void);
extern void lexer_invalid_type_suffix_reset(void);
extern int32_t lexer_invalid_type_suffix_pending(void);
extern void lexer_invalid_escape_reset(void);
extern int32_t lexer_invalid_escape_pending(void);
struct parser_ParseIntoResult parser_parse_into_apply_unclosed_gate(struct parser_ParseIntoResult r) {
  if (lexer_unclosed_block_comment_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_unclosed_string_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_illegal_char_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_hex_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_exp_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_bin_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  if (lexer_incomplete_oct_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  if (lexer_invalid_digit_sep_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  if (lexer_invalid_type_suffix_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  /* wave281: invalid string escape hard fail (not silent keep). */
  if (lexer_invalid_escape_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  /* wave283: string lit capacity overflow hard fail (not silent truncate). */
  if (lexer_string_lit_overflow_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  /* wave284: identifier span >63 hard fail (not silent clamp / XP003). */
  if (lexer_ident_too_long_pending() != 0) {
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  }
  if (lexer_incomplete_bin_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_oct_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  return r;
}
/*
 * wave424 Cap residual pure — finish successful parse_into with trait completeness.
 * Root: freestanding -o calls parser_parse_into_buf directly (skips with_init check).
 * G.7: single finish helper; pin ≡ parser.x parse_into_finish_ok.
 * PLATFORM: SHARED parse.
 */
extern int32_t xlang_trait_check_impls_complete_c(void *module);
static struct parser_ParseIntoResult parser_parse_into_finish_ok(struct ast_Module *module, int32_t main_idx) {
  struct parser_ParseIntoResult r =
      parser_parse_into_apply_unclosed_gate((struct parser_ParseIntoResult){ .ok = 0, .main_idx = main_idx });
  if (r.ok != 0)
    return r;
  if (xlang_trait_check_impls_complete_c((void *)module) != 0)
    return (struct parser_ParseIntoResult){ .ok = 1, .main_idx = -1 };
  return r;
}
struct parser_ParseIntoResult parser_parse_into_result_empty_module_or_fail_tok(int32_t fail_tok) {
  /* wave269: unclosed block comment at EOF is hard fail (not empty-module success). */
  if (lexer_unclosed_block_comment_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave271: unclosed string at EOF is hard fail (not empty-module success / soft P001). */
  if (lexer_unclosed_string_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave272: illegal/unknown byte is hard fail (not soft P001 "no functions"). */
  if (lexer_illegal_char_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave273: incomplete hex is hard fail (not silent 0 / soft P001). */
  if (lexer_incomplete_hex_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_exp_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave276: incomplete binary/octal hard fail. */
  if (lexer_incomplete_bin_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_incomplete_oct_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave278: invalid digit separator hard fail (not soft XP003). */
  if (lexer_invalid_digit_sep_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if (lexer_invalid_type_suffix_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave281: invalid string escape hard fail (not silent keep). */
  if (lexer_invalid_escape_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave283: string lit capacity overflow hard fail (not silent truncate). */
  if (lexer_string_lit_overflow_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  /* wave284: identifier span >63 hard fail (not silent clamp / XP003). */
  if (lexer_ident_too_long_pending() != 0)
    return (struct parser_ParseIntoResult){ .ok = -1, .main_idx = -1 };
  if ((fail_tok ==((int32_t)(130)))) {
    return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
  }
  return (struct parser_ParseIntoResult){ .ok = 0, .main_idx = -(1) };
}
void parser_copy_slice_to_name64(struct xlang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t * out) {
  {
    int32_t i = 0;
    while ((i < nlen)) {
      if (((start + ((size_t)(i))) < (source->length))) {
        (void)(((out)[i] = (source)->data[(start + ((size_t)(i)))]));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_copy_slice_to_name64_at_end(struct xlang_slice_uint8_t * source, size_t end_pos, int32_t nlen, uint8_t * out) {
  {
    size_t start = (end_pos - ((size_t)(nlen)));
    (void)(parser_copy_slice_to_name64(source, start, nlen, out));
  }
}
extern int32_t parser_struct_field_name_from_tok_glue(struct lexer_LexerResult r, struct xlang_slice_uint8_t * source, uint8_t * out);
int32_t parser_struct_field_name_from_tok(struct lexer_LexerResult r, struct xlang_slice_uint8_t * source, uint8_t * out) {
  return parser_struct_field_name_from_tok_glue(r, source, out);
  return 0;
}
int32_t parser_struct_field_name_from_tok_buf(struct lexer_LexerResult r, uint8_t * data, int32_t len, uint8_t * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_struct_field_name_from_tok(r, &(slice), out);
  }
  return 0;
}
int parser_struct_field_name_tok_kind(enum token_TokenKind k) {
  {
    if ((k ==59)) {
      return 1;
    }
    int32_t ko = ((int32_t)(k));
    if ((ko ==18)) {
      return 1;
    }
    if ((ko ==17)) {
      return 1;
    }
    return 0;
  }
}
int parser_struct_field_continues_tok_kind(enum token_TokenKind k) {
  {
    if (parser_struct_field_name_tok_kind(k)) {
      return 1;
    }
    int32_t ko = ((int32_t)(k));
    if ((ko ==20)) {
      return 1;
    }
    return 0;
  }
}
int parser_token_is_label_start(struct lexer_LexerResult r, struct xlang_slice_uint8_t * source) {
  {
    if ((((r.tok).kind) !=59)) {
      return 0;
    }
    struct lexer_LexerResult nx = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    (void)(lexer_next_into(&(nx), (r.next_lex), source));
    return (((nx.tok).kind) ==91);
  }
}
void parser_copy_slice_to_param32(struct xlang_slice_uint8_t * source, size_t start, int32_t nlen, uint8_t * out) {
  {
    int32_t i = 0;
    /* wave585 Cap residual: fill 128-byte row (ABI name *param32). */
    while ((i < 128)) {
      if (((i < nlen) && ((start + ((size_t)(i))) < (source->length)))) {
        (void)(((out)[i] = (source)->data[(start + ((size_t)(i)))]));
      } else {
        (void)(((out)[i] = 0));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_copy_slice_to_param32_at_end(struct xlang_slice_uint8_t * source, size_t end_pos, int32_t nlen, uint8_t * out) {
  {
    size_t start = (end_pos - ((size_t)(nlen)));
    (void)(parser_copy_slice_to_param32(source, start, nlen, out));
  }
}
void parser_copy_slice_to_name64_buf(uint8_t * source, int32_t source_len, size_t start, int32_t nlen, uint8_t * out) {
  {
    int32_t i = 0;
    while ((i < nlen)) {
      if (((start + ((size_t)(i))) < ((size_t)(source_len)))) {
        (void)(((out)[i] = (source)[(start + ((size_t)(i)))]));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_copy_slice_to_name64_at_end_buf(uint8_t * source, int32_t source_len, size_t end_pos, int32_t nlen, uint8_t * out) {
  {
    size_t start = (end_pos - ((size_t)(nlen)));
    (void)(parser_copy_slice_to_name64_buf(source, source_len, start, nlen, out));
  }
}
void parser_copy_slice_to_param32_at_end_buf(uint8_t * source, int32_t source_len, size_t end_pos, int32_t nlen, uint8_t * out) {
  {
    size_t start = (end_pos - ((size_t)(nlen)));
    int32_t i = 0;
    while ((i < 128)) {
      if (((i < nlen) && ((start + ((size_t)(i))) < ((size_t)(source_len))))) {
        (void)(((out)[i] = (source)[(start + ((size_t)(i)))]));
      } else {
        (void)(((out)[i] = 0));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_copy_slice_to_param32_buf(uint8_t * source, int32_t source_len, size_t start, int32_t nlen, uint8_t * out) {
  {
    int32_t i = 0;
    while ((i < 128)) {
      if (((i < nlen) && ((start + ((size_t)(i))) < ((size_t)(source_len))))) {
        (void)(((out)[i] = (source)[(start + ((size_t)(i)))]));
      } else {
        (void)(((out)[i] = 0));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_parse_one_function_impl(struct parser_OneFuncResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  {
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(out)));
    struct parser_OneFuncResult out_clean = parser_onefunc_alloc_wired_for_parse(lex);
    (void)(parser_copy_onefunc_into(out, &(out_clean)));
    /* Cap 10.7.1: clear variadic until trailing `...` is seen (≡ parser.x). */
    (void)(((out->is_variadic) = 0));
    struct parser_OneFuncResult * out_ref = out;
    uint8_t dummy_name[128] = {};
    struct parser_OneFuncResult impl_snap = parser_onefunc_scratch_empty();
    (void)(ast_pool_onefunc_reset(parser_onefunc_result_pool_ptr(&(impl_snap))));
    (void)(parser_onefunc_res_wire_dummy_head(&(impl_snap), lex, dummy_name));
    (void)(parser_onefunc_res_wire_dummy_const_let(&(impl_snap)));
    (void)(parser_onefunc_res_wire_dummy_if_mul(&(impl_snap)));
    (void)(parser_onefunc_res_wire_dummy_call_binop(&(impl_snap), dummy_name));
    (void)(parser_onefunc_res_wire_dummy_loop_call(&(impl_snap)));
    (void)(parser_onefunc_res_wire_dummy_for_if(&(impl_snap)));
    int return_type_is_bool = 0;
    int32_t return_expr_ref_storage = 0;
    size_t name_start = ((size_t)(0));
    int32_t func_name_len_storage[1] = {};
    struct lexer_Lexer lex_before_ret = (struct lexer_Lexer){ .pos = ((size_t)(0)), .line = 0, .col = 0 };
    int32_t ret_type_ref = 0;
    struct lexer_Lexer lex_before_type = (struct lexer_Lexer){ .pos = ((size_t)(0)), .line = 0, .col = 0 };
    int32_t type_ref_param = 0;
    int32_t plen_param = 0;
    int32_t param_idx = 0;
    uint8_t * param_pool = ((uint8_t *)(0));
    uint8_t pname_row[128] = {};
    int32_t zi_param = 0;
    struct lexer_LexerResult r = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) ==59)) {
    } else {
      if ((((r.tok).kind) ==58)) {
        (void)(((func_name_len_storage)[0] = 5));
        (void)(((dummy_name)[0] = 115));
        (void)(((dummy_name)[1] = 112));
        (void)(((dummy_name)[2] = 97));
        (void)(((dummy_name)[3] = 119));
        (void)(((dummy_name)[4] = 110));
        (void)(parser_lex_from_next_into(&(lex), r));
      } else {
        if ((((r.tok).kind) !=1)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==58)) {
          (void)(((func_name_len_storage)[0] = 5));
          (void)(((dummy_name)[0] = 115));
          (void)(((dummy_name)[1] = 112));
          (void)(((dummy_name)[2] = 97));
          (void)(((dummy_name)[3] = 119));
          (void)(((dummy_name)[4] = 110));
          (void)(parser_lex_from_next_into(&(lex), r));
        } else {
          if ((((r.tok).kind) !=59)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          } else {
            (void)(((func_name_len_storage)[0] = ((r.tok).ident_len)));
            if ((((func_name_len_storage)[0] <=0) || ((func_name_len_storage)[0] > 127))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((name_start = (((r.next_lex).pos) - (func_name_len_storage)[0])));
            (void)(parser_copy_slice_to_name64(source, name_start, (func_name_len_storage)[0], &((dummy_name)[0])));
            (void)(parser_lex_from_next_into(&(lex), r));
          }
        }
      }
    }
    if (((func_name_len_storage)[0] ==0)) {
      if ((((r.tok).kind) !=59)) {
        (void)(parser_set_onefunc_fail(out, lex));
        return;
      }
      (void)(((func_name_len_storage)[0] = ((r.tok).ident_len)));
      if ((((func_name_len_storage)[0] <=0) || ((func_name_len_storage)[0] > 127))) {
        (void)(parser_set_onefunc_fail(out, lex));
        return;
      }
      (void)((name_start = (((r.next_lex).pos) - (func_name_len_storage)[0])));
      (void)(parser_copy_slice_to_name64(source, name_start, (func_name_len_storage)[0], &((dummy_name)[0])));
      (void)(parser_lex_from_next_into(&(lex), r));
    }
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) ==120)) {
      int32_t generic_n = 0;
      extern int32_t xlang_generic_func_register_pending_type_params_c(const uint8_t *fn_name, int32_t fn_name_len);
      (void)(parser_skip_generic_angle_list_count_into_glue(&(lex), &(generic_n), lex, source));
      (void)(((out->num_generic_params) = generic_n));
      /* wave455: snapshot pending type-param names under this function name
       * before body parse overwrites pending via call-site turbofish counts.
       * PLATFORM: SHARED — G.7 register + typeck ret fixup. */
      if ((generic_n > 0) && ((func_name_len_storage)[0] > 0)) {
        (void)(xlang_generic_func_register_pending_type_params_c(&((dummy_name)[0]), (func_name_len_storage)[0]));
      }
      (void)(lexer_next_into(&(r), lex, source));
    }
    if ((((r.tok).kind) !=82)) {
      (void)(parser_set_onefunc_fail(out, lex));
      return;
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) ==83)) {
      (void)(parser_lex_from_next_into(&(lex), r));
    } else {
      while ((1 ==1)) {
        /* Cap 10.7.1 language slice5: trailing `...` (TOKEN_ELLIPSIS=94) after ≥1 named
         * formal. Mirrors parser.x; codegen emits `, ...` when is_variadic. PLATFORM: SHARED. */
        if ((((r.tok).kind) ==94)) {
          if (((out->num_params) <=0)) {
            (void)(parser_set_onefunc_fail(out_ref, lex));
            return;
          }
          (void)(((out->is_variadic) = 1));
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=83)) {
            (void)(parser_set_onefunc_fail(out_ref, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          break;
        }
        /* 59=TOKEN_IDENT, 51=TOKEN_SELF: accept self as param binding name.
         * Lexer keywords self as TOKEN_SELF with ident_len=0; IDENT-only check
         * silent set_onefunc_fail → function dropped from multi-fn AST (wave43).
         * Other keywords: P014 hard (twin of parser.x / body-lets `let run`). */
        if (((((r.tok).kind) !=59) && (((r.tok).kind) !=51))) {
          {
            extern void parser_report_keyword_binding_p014_c(int32_t line, int32_t col);
            parser_report_keyword_binding_p014_c((int32_t)((r.tok).line), (int32_t)((r.tok).col));
          }
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        if ((((r.tok).kind) ==51)) {
          (void)((plen_param = 4));
        } else {
          (void)((plen_param = ((r.tok).ident_len)));
        }
        if (((plen_param <=0) || (plen_param > 127))) {
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        (void)((zi_param = 0));
        while ((zi_param < 128)) {
          (void)(((pname_row)[zi_param] = 0));
          (void)((zi_param = (zi_param + 1)));
        }
        (void)(parser_copy_slice_to_param32(source, (r.token_start), plen_param, &((pname_row)[0])));
        (void)((param_pool = parser_onefunc_result_pool_ptr(out)));
        /* wave679 Cap residual: duplicate param name → P012 hard-fail (host BLD001). PLATFORM: SHARED */
        {
          extern int32_t parser_onefunc_param_name_dup_c(uint8_t *pool, int32_t nparams, uint8_t *name,
                                                        int32_t name_len);
          extern void parser_report_duplicate_name_p012_c(int32_t line, int32_t col, int32_t kind);
          if (parser_onefunc_param_name_dup_c(param_pool, (int32_t)(out->num_params), &((pname_row)[0]),
                                              plen_param) != 0) {
            (void)(parser_report_duplicate_name_p012_c((int32_t)((r.tok).line), (int32_t)((r.tok).col), 0));
            (void)(parser_set_onefunc_fail(out_ref, lex));
            return;
          }
        }
        (void)((param_idx = pipeline_onefunc_append_param(param_pool, &((pname_row)[0]), plen_param, 0)));
        if ((param_idx < 0)) {
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        (void)(((out->num_params) = (param_idx + 1)));
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        /* wave676: param requires `: Type`; silent set_onefunc_fail was soft residual. */
        if ((((r.tok).kind) !=91)) {
          extern void parser_report_untyped_formal_p011_c(int32_t line, int32_t col, int32_t kind);
          (void)(parser_report_untyped_formal_p011_c((int32_t)((r.tok).line), (int32_t)((r.tok).col), 0));
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)((lex_before_type = lex));
        (void)((type_ref_param = parser_parse_type_ref_for_arena_into(arena, lex_before_type, source, &(lex))));
        if ((type_ref_param ==0)) {
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        (void)(pipeline_onefunc_set_param_type_ref(param_pool, param_idx, type_ref_param));
        (void)(driver_diagnostic_parser_onefunc_param_ref(&((dummy_name)[0]), (func_name_len_storage)[0], &((pname_row)[0]), plen_param, 0, param_idx, type_ref_param));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==83)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          break;
        }
        if ((((r.tok).kind) !=90)) {
          (void)(parser_set_onefunc_fail(out_ref, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==83)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          break;
        }
      }
    }
    (void)(lexer_next_into(&(r), lex, source));
    /* wave676: `): Type` required; missing return type was silent drop. */
    if ((((r.tok).kind) !=91)) {
      extern void parser_report_untyped_formal_p011_c(int32_t line, int32_t col, int32_t kind);
      (void)(parser_report_untyped_formal_p011_c((int32_t)((r.tok).line), (int32_t)((r.tok).col), 1));
      (void)(parser_set_onefunc_fail(out_ref, lex));
      return;
    }
    (void)(parser_lex_from_next_into(&(lex), r));
    (void)((lex_before_ret = lex));
    (void)((ret_type_ref = parser_parse_type_ref_for_arena_into(arena, lex_before_ret, source, &(lex))));
    if ((ret_type_ref ==0)) {
      (void)(parser_set_onefunc_fail(out, lex));
      return;
    }
    (void)(((out->func_return_type_ref) = ret_type_ref));
    if ((ret_type_ref !=0)) {
      struct ast_Type rt = ast_ast_arena_type_get(arena, ret_type_ref);
      if (((rt.kind) ==1)) {
        (void)((return_type_is_bool = 1));
      }
    }
    (void)(lexer_next_into(&(r), lex, source));
    if ((((r.tok).kind) !=84)) {
      (void)(parser_set_onefunc_fail(out, lex));
      return;
    }
    if ((((r.tok).kind) ==84)) {
      (void)(parser_lex_from_next_into(&(lex), r));
      (void)(((out->num_src_stmt_order) = 0));
      (void)(((out->num_src_body_expr_stmts) = 0));
      if (!(parser_parse_body_lets_into(arena, lex, source, out, &(lex)))) {
        (void)(parser_set_onefunc_fail(out, lex));
        return;
      }
      (void)(((out->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out))));
      (void)(((out->num_consts) = pipeline_onefunc_num_consts(parser_onefunc_result_pool_ptr(out))));
      int32_t csr0 = 0;
      while ((csr0 < (out->num_consts))) {
        (void)(parser_onefunc_push_src_stmt(out, 0, csr0));
        (void)((csr0 = (csr0 + 1)));
      }
      int32_t lsr = 0;
      while ((lsr < (out->num_lets))) {
        (void)(parser_onefunc_push_src_stmt(out, 1, lsr));
        (void)((lsr = (lsr + 1)));
      }
      struct lexer_LexerResult r_peek = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
      (void)(lexer_next_into(&(r_peek), lex, source));
      (void)((r = r_peek));
      (void)((lex = parser_rewind_lex_for_following_stmt(lex, r_peek)));
      int stmt_tok_ready = 1;
      struct lexer_Lexer stmt_start = (struct lexer_Lexer){ .pos = ((size_t)(0)), .line = 0, .col = 0 };
      struct parser_ParseExprResult expr_stmt_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = stmt_start };
      int32_t ex_i = 0;
      while ((1 ==1)) {
        if (!(stmt_tok_ready)) {
          (void)(lexer_next_into(&(r), lex, source));
        }
        (void)((stmt_tok_ready = 0));
        if ((((r.tok).kind) ==59)) {
          size_t ret_id_start = (r.token_start);
          if ((ret_id_start ==0)) {
            (void)((ret_id_start = parser_lexer_pos_before_run(((r.next_lex).pos), ((r.tok).ident_len))));
          }
          if (parser_return_kw_immediately_before(source, ret_id_start)) {
            struct lexer_Lexer ret_kw_lex = (struct lexer_Lexer){ .pos = (ret_id_start - 7), .line = ((r.tok).line), .col = ((r.tok).col) };
            struct lexer_LexerResult r_ret_kw = (struct lexer_LexerResult){ .next_lex = ret_kw_lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
            (void)(lexer_next_into(&(r_ret_kw), ret_kw_lex, source));
            (void)((r = r_ret_kw));
            (void)((lex = ret_kw_lex));
          }
        }
        /* wave379: only RBRACE/EOF break; mid-body RETURN as expr_stmt */
        if ((((((r.tok).kind) ==85) || (((r.tok).kind) ==0)))) {
          break;
        }
        if ((((r.tok).kind) ==11)) {
          /* wave656: onefunc bare return ASI + Cap-T001 (mirror parser.x wave655/656).
           * G.7: advance_past_stmt_semicolon_into after operand; Cap-T001 skip filler.
           * PLATFORM: SHARED — seed pin same commit as parser.x. */
          (void)(parser_lex_from_next_into(&(lex), r));
          struct parser_ParseExprResult ret_mid_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          (void)(lexer_next_into(&(r), lex, source));
          if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
            (void)(parser_parse_expr_into(arena, lex, source, &(ret_mid_res)));
            if (!((ret_mid_res.ok))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((lex = (ret_mid_res.next_lex)));
            if ((parser_advance_past_stmt_semicolon_into(&(r), lex, source) ==0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
          }
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if (parser_token_is_label_start(r, source)) {
            int32_t ret_mid_ref = ast_ast_arena_expr_alloc(arena);
            if ((ret_mid_ref ==0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            struct ast_Expr re_mid = ast_ast_arena_expr_get(arena, ret_mid_ref);
            (void)(((re_mid.kind) = 41));
            (void)(((re_mid.line) = 0));
            (void)(((re_mid.col) = 0));
            (void)(parser_expr_set_common_zeros(&(re_mid)));
            if ((ret_mid_res.ok)) {
              (void)(((re_mid.unary_operand_ref) = (ret_mid_res.expr_ref)));
            }
            (void)(ast_ast_arena_expr_set(arena, ret_mid_ref, re_mid));
            int32_t ex_ret_i = pipeline_onefunc_push_body_expr_stmt(parser_onefunc_result_pool_ptr(out), ret_mid_ref);
            if ((ex_ret_i < 0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(((out->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(out))));
            (void)(parser_onefunc_push_src_stmt(out, 2, ex_ret_i));
            (void)(((impl_snap.has_explicit_return_kw) = 1));
            (void)((stmt_tok_ready = 1));
            continue;
          }
          (void)(((impl_snap.has_explicit_return_kw) = 1));
          (void)(((impl_snap.has_final_expr) = 1));
          if ((ret_mid_res.ok)) {
            (void)((return_expr_ref_storage = (ret_mid_res.expr_ref)));
          } else {
            int32_t bare_fin = ast_ast_arena_expr_alloc(arena);
            if ((bare_fin ==0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            struct ast_Expr re_fin = ast_ast_arena_expr_get(arena, bare_fin);
            (void)(((re_fin.kind) = 41));
            (void)(((re_fin.line) = 0));
            (void)(((re_fin.col) = 0));
            (void)(parser_expr_set_common_zeros(&(re_fin)));
            (void)(ast_ast_arena_expr_set(arena, bare_fin, re_fin));
            (void)((return_expr_ref_storage = bare_fin));
          }
          if (((((r.tok).kind) !=85) && (((r.tok).kind) !=0))) {
            while (((((r.tok).kind) !=85) && (((r.tok).kind) !=0))) {
              (void)(parser_lex_from_next_into(&(lex), r));
              (void)(lexer_next_into(&(r), lex, source));
            }
          }
          if ((((r.tok).kind) !=85)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
          return;
        }
        if (((((r.tok).kind) ==2) || (((r.tok).kind) ==3))) {
          /* Mid-body let/const: push kind=0 consts then kind=1 lets (prefix face). */
          int32_t n_before_mid = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out));
          int32_t n_const_before = pipeline_onefunc_num_consts(parser_onefunc_result_pool_ptr(out));
          int32_t kw_back = 3;
          if ((((r.tok).kind) ==3)) {
            (void)((kw_back = 5));
          }
          struct lexer_Lexer lex_mid_let = (struct lexer_Lexer){ .pos = parser_lexer_pos_before_run(((r.next_lex).pos), kw_back), .line = ((r.tok).line), .col = ((r.tok).col) };
          if (!(parser_parse_body_lets_into(arena, lex_mid_let, source, out, &(lex)))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((out->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out))));
          (void)(((out->num_consts) = pipeline_onefunc_num_consts(parser_onefunc_result_pool_ptr(out))));
          int32_t push_ci = n_const_before;
          while ((push_ci < (out->num_consts))) {
            (void)(parser_onefunc_push_src_stmt(out, 0, push_ci));
            (void)((push_ci = (push_ci + 1)));
          }
          int32_t push_mi = n_before_mid;
          while ((push_mi < (out->num_lets))) {
            (void)(parser_onefunc_push_src_stmt(out, 1, push_mi));
            (void)((push_mi = (push_mi + 1)));
          }
          (void)(lexer_next_into(&(r), lex, source));
          continue;
        }
        if ((((r.tok).kind) ==13)) {
          struct parser_ParseBlockResult block_res_def_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t def_idx_fn = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)((block_res_def_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_def_fn)));
          if (!((block_res_def_fn.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((def_idx_fn = pipeline_onefunc_append_defer(parser_onefunc_result_pool_ptr(out), (block_res_def_fn.block_ref))));
          if ((def_idx_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (block_res_def_fn.next_lex)));
          /* Optional `;` after defer {…} (function-body compound ASI).
           * `defer { k = 1 }; return k` used to P001. No-semi stays stmt head.
           * kind 95 = TOKEN_SEMICOLON. Do not realign. PLATFORM: SHARED. */
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)((stmt_tok_ready = 0));
          } else {
            (void)((stmt_tok_ready = 1));
          }
          continue;
        }
        if ((((r.tok).kind) ==17)) {
          struct parser_ParseExprResult cap_res_fn = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          struct parser_ParseBlockResult block_res_wa_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t wa_idx_fn = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=82)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)((cap_res_fn = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
          (void)(parser_parse_expr_into(arena, lex, source, &(cap_res_fn)));
          if ((!((cap_res_fn.ok)) || ((cap_res_fn.expr_ref) ==0))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (cap_res_fn.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=83)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)((block_res_wa_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_wa_fn)));
          if (!((block_res_wa_fn.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((wa_idx_fn = pipeline_onefunc_append_with_arena(parser_onefunc_result_pool_ptr(out), (cap_res_fn.expr_ref), (block_res_wa_fn.block_ref))));
          if ((wa_idx_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_onefunc_push_src_stmt(out, 6, wa_idx_fn));
          (void)((lex = (block_res_wa_fn.next_lex)));
          /* Optional `;` after with_arena(cap) {…} (function-body compound ASI).
           * `with_arena(64) { let x = 1; }; return` used to P001. No-semi stays
           * stmt head. kind 95 = TOKEN_SEMICOLON. Do not realign. PLATFORM: SHARED. */
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)((stmt_tok_ready = 0));
          } else {
            (void)((stmt_tok_ready = 1));
          }
          continue;
        }
        if ((((r.tok).kind) ==16)) {
          uint8_t reg_nm_fn[128] = {};
          int32_t reg_nlen_fn = 0;
          struct parser_ParseBlockResult block_res_reg_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t reg_idx_fn = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=59)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_copy_slice_to_name64(source, (r.token_start), ((r.tok).ident_len), &((reg_nm_fn)[0])));
          (void)((reg_nlen_fn = ((r.tok).ident_len)));
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)((block_res_reg_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_reg_fn)));
          if (!((block_res_reg_fn.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((reg_idx_fn = pipeline_onefunc_append_region(parser_onefunc_result_pool_ptr(out), &((reg_nm_fn)[0]), reg_nlen_fn, (block_res_reg_fn.block_ref))));
          if ((reg_idx_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_onefunc_push_src_stmt(out, 6, reg_idx_fn));
          (void)((lex = (block_res_reg_fn.next_lex)));
          /* Optional `;` after region label {…} (function-body compound ASI).
           * `region foo { k = 1 }; return k` used to P001. No-semi stays stmt
           * head. kind 95 = TOKEN_SEMICOLON. Do not realign. PLATFORM: SHARED. */
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)((stmt_tok_ready = 0));
          } else {
            (void)((stmt_tok_ready = 1));
          }
          continue;
        }
        if (((((r.tok).kind) ==59) && (((r.tok).ident_len) ==6))) {
          uint8_t unsafe_nm_fn[128] = {};
          (void)(parser_copy_slice_to_name64(source, (r.token_start), ((r.tok).ident_len), &((unsafe_nm_fn)[0])));
          if ((((((((unsafe_nm_fn)[0] ==117) && ((unsafe_nm_fn)[1] ==110)) && ((unsafe_nm_fn)[2] ==115)) && ((unsafe_nm_fn)[3] ==97)) && ((unsafe_nm_fn)[4] ==102)) && ((unsafe_nm_fn)[5] ==101))) {
            struct parser_ParseBlockResult block_res_unsafe_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
            int32_t unsafe_idx_fn = 0;
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
            if ((((r.tok).kind) !=84)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)((block_res_unsafe_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
            (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_unsafe_fn)));
            if (!((block_res_unsafe_fn.ok))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((unsafe_idx_fn = pipeline_onefunc_append_unsafe(parser_onefunc_result_pool_ptr(out), (block_res_unsafe_fn.block_ref))));
            if ((unsafe_idx_fn < 0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_onefunc_push_src_stmt(out, 6, unsafe_idx_fn));
            (void)((lex = (block_res_unsafe_fn.next_lex)));
            (void)((stmt_tok_ready = 0));
            continue;
          }
        }
        /* wave379: bare goto (onefunc); TOKEN_GOTO=48 */
        if ((((r.tok).kind) ==48)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=59)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          int32_t goto_len_fn = ((r.tok).ident_len);
          size_t goto_start_fn = (r.token_start);
          if ((goto_start_fn ==0)) {
            (void)((goto_start_fn = parser_lexer_pos_before_run(((r.next_lex).pos), goto_len_fn)));
          }
          uint8_t goto_row_fn[128] = {};
          (void)(parser_copy_slice_to_param32(source, goto_start_fn, goto_len_fn, &((goto_row_fn)[0])));
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
          }
          int32_t li_g_fn = pipeline_onefunc_append_labeled(parser_onefunc_result_pool_ptr(out), ((uint8_t *)(0)), 0, 1, &((goto_row_fn)[0]), goto_len_fn, 0);
          if ((li_g_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_onefunc_push_src_stmt(out, 7, li_g_fn));
          (void)((stmt_tok_ready = 1));
          continue;
        }
        if (parser_token_is_label_start(r, source)) {
          int32_t label_len_fn = ((r.tok).ident_len);
          size_t label_start_fn = (r.token_start);
          if ((label_start_fn ==0)) {
            (void)((label_start_fn = parser_lexer_pos_before_run(((r.next_lex).pos), label_len_fn)));
          }
          uint8_t label_row_fn[128] = {};
          (void)(parser_copy_slice_to_param32(source, label_start_fn, label_len_fn, &((label_row_fn)[0])));
          struct lexer_LexerResult colon_fn = (struct lexer_LexerResult){ .next_lex = (r.next_lex), .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
          (void)(lexer_next_into(&(colon_fn), (r.next_lex), source));
          (void)((lex = (colon_fn.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==11)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            struct parser_ParseExprResult ret_val_fn = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
            (void)(lexer_next_into(&(r), lex, source));
            if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
              (void)(parser_parse_expr_into(arena, lex, source, &(ret_val_fn)));
              if (!((ret_val_fn.ok))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)((lex = (ret_val_fn.next_lex)));
              (void)(lexer_next_into(&(r), lex, source));
            }
            if ((((r.tok).kind) ==95)) {
              (void)(parser_lex_from_next_into(&(lex), r));
              (void)(lexer_next_into(&(r), lex, source));
            }
            int32_t ret_op_fn = 0;
            if ((ret_val_fn.ok)) {
              (void)((ret_op_fn = (ret_val_fn.expr_ref)));
            }
            int32_t li_lr = pipeline_onefunc_append_labeled(parser_onefunc_result_pool_ptr(out), &((label_row_fn)[0]), label_len_fn, 0, ((uint8_t *)(0)), 0, ret_op_fn);
            if ((li_lr < 0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_onefunc_push_src_stmt(out, 7, li_lr));
            /* wave383: pin final return when L:return e; is last before } so asm
             * backends that ignore kind=7 still emit the value (goto main → 42).
             * PLATFORM: SHARED — mirror parser.x. */
            if (((((r.tok).kind) ==85) && (ret_op_fn != 0))) {
              (void)((return_expr_ref_storage = ret_op_fn));
              (void)(((impl_snap.has_final_expr) = 1));
              (void)(((impl_snap.has_explicit_return_kw) = 1));
            }
            (void)((stmt_tok_ready = 1));
            continue;
          }
          if ((((r.tok).kind) ==48)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
            if ((((r.tok).kind) !=59)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            int32_t gtn_fn = ((r.tok).ident_len);
            size_t gts_fn = (r.token_start);
            if ((gts_fn ==0)) {
              (void)((gts_fn = parser_lexer_pos_before_run(((r.next_lex).pos), gtn_fn)));
            }
            uint8_t gtr_fn[128] = {};
            (void)(parser_copy_slice_to_param32(source, gts_fn, gtn_fn, &((gtr_fn)[0])));
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
            if ((((r.tok).kind) ==95)) {
              (void)(parser_lex_from_next_into(&(lex), r));
              (void)(lexer_next_into(&(r), lex, source));
            }
            int32_t li_lab2 = pipeline_onefunc_append_labeled(parser_onefunc_result_pool_ptr(out), &((label_row_fn)[0]), label_len_fn, 0, ((uint8_t *)(0)), 0, 0);
            if ((li_lab2 < 0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_onefunc_push_src_stmt(out, 7, li_lab2));
            int32_t li_gt2 = pipeline_onefunc_append_labeled(parser_onefunc_result_pool_ptr(out), ((uint8_t *)(0)), 0, 1, &((gtr_fn)[0]), gtn_fn, 0);
            if ((li_gt2 < 0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_onefunc_push_src_stmt(out, 7, li_gt2));
            (void)((stmt_tok_ready = 1));
            continue;
          }
          int32_t li_pure_fn = pipeline_onefunc_append_labeled(parser_onefunc_result_pool_ptr(out), &((label_row_fn)[0]), label_len_fn, 0, ((uint8_t *)(0)), 0, 0);
          if ((li_pure_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_onefunc_push_src_stmt(out, 7, li_pure_fn));
          (void)((stmt_tok_ready = 1));
          continue;
        }
        if ((((r.tok).kind) ==7)) {
          int32_t cond_ref_loop = 0;
          struct parser_ParseBlockResult block_res_loop = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t while_idx_loop = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)((cond_ref_loop = parser_alloc_true_bool_lit(arena)));
          if ((cond_ref_loop ==0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((block_res_loop = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_loop)));
          if (!((block_res_loop.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((while_idx_loop = pipeline_onefunc_append_while(parser_onefunc_result_pool_ptr(out), cond_ref_loop, (block_res_loop.block_ref))));
          if ((while_idx_loop < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((impl_snap.num_loops) = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(out))));
          (void)(parser_onefunc_push_src_stmt(out, 3, while_idx_loop));
          (void)((lex = (block_res_loop.next_lex)));
          (void)((stmt_tok_ready = 0));
          continue;
        }
        if ((((r.tok).kind) ==6)) {
          struct lexer_Lexer while_cond_start = lex;
          struct parser_ParseExprResult expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          int32_t cond_ref = 0;
          struct parser_ParseBlockResult block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t while_idx = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          /* wave361/wave650: bare while cond (docs/03); do not strip LPAREN (82). */
          (void)((lex = parser_lex_at_token_from_result(r)));
          (void)((while_cond_start = lex));
          (void)((expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = while_cond_start }));
          (void)(parser_parse_cond_expr_into(arena, while_cond_start, source, &(expr_res)));
          if (!((expr_res.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((cond_ref = (expr_res.expr_ref)));
          (void)((lex = (expr_res.next_lex)));
          if ((parser_advance_past_cond_rparen_into(&(r), lex, source) ==0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)((block_res = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res)));
          if (!((block_res.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((while_idx = pipeline_onefunc_append_while(parser_onefunc_result_pool_ptr(out), cond_ref, (block_res.block_ref))));
          if ((while_idx < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((impl_snap.num_loops) = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(out))));
          (void)(parser_onefunc_push_src_stmt(out, 3, while_idx));
          (void)((lex = (block_res.next_lex)));
          (void)((stmt_tok_ready = 0));
          continue;
        }
        if ((((r.tok).kind) ==8)) {
          int32_t init_ref = 0;
          int32_t for_cond_ref = 0;
          int32_t step_ref = 0;
          struct parser_ParseBlockResult block_res_f = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t for_idx = 0;
          struct parser_ParseExprResult expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          struct parser_ParseExprResult expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          struct parser_ParseExprResult expr_res_fs = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex };
          int32_t cond_expr_ref = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=82)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          /* wave347: for-init let (TOKEN_LET=2) — onefunc body-lets + push kind=1; init_ref=0. */
          int for_past_init_semi_fn = 0;
          if ((((r.tok).kind) !=95)) {
            if ((((r.tok).kind) ==2)) {
              int32_t n_before_fi = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out));
              struct lexer_Lexer lex_fi_let = (struct lexer_Lexer){
                .pos = parser_lexer_pos_before_run(((r.next_lex).pos), 3),
                .line = ((r.tok).line),
                .col = ((r.tok).col)
              };
              if (!(parser_parse_body_lets_into(arena, lex_fi_let, source, out, &(lex)))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)(((out->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out))));
              int32_t push_fi = n_before_fi;
              while ((push_fi < (out->num_lets))) {
                (void)(parser_onefunc_push_src_stmt(out, 1, push_fi));
                (void)((push_fi = (push_fi + 1)));
              }
              (void)((init_ref = 0));
              (void)((for_past_init_semi_fn = 1));
              (void)(lexer_next_into(&(r), lex, source));
            } else {
              /*
               * wave701: range-for `for (i : lo .. hi) { body }` desugar.
               * TOKEN_IDENT then TOKEN_COLON → let i=lo; for (; i<hi; i=i+1) body.
               * PLATFORM: SHARED — Cap residual; G.7 with parser.x twin when regenerated.
               */
              int range_for_done = 0;
              if ((((r.tok).kind) == token_TokenKind_TOKEN_IDENT)) {
                struct lexer_LexerResult r_peek;
                (void)(lexer_next_into(&(r_peek), (r.next_lex), source));
                if ((((r_peek.tok).kind) == token_TokenKind_TOKEN_COLON)) {
                  uint8_t rf_name[128];
                  int32_t rf_nlen = ((r.tok).ident_len);
                  size_t rf_nstart = (r.token_start);
                  int32_t rf_ni = 0;
                  int32_t lo_ref = 0;
                  int32_t hi_ref = 0;
                  int32_t v1 = 0;
                  int32_t v2 = 0;
                  int32_t v3 = 0;
                  int32_t one_ref = 0;
                  int32_t lt_ref = 0;
                  int32_t add_ref = 0;
                  int32_t asg_ref = 0;
                  int32_t i32ty = 0;
                  int32_t let_i = 0;
                  struct ast_Expr ve;
                  if (rf_nlen > 127) rf_nlen = 127;
                  for (rf_ni = 0; rf_ni < 128; rf_ni++) rf_name[rf_ni] = 0;
                  for (rf_ni = 0; rf_ni < rf_nlen && rf_nstart + (size_t)rf_ni < (source->length); rf_ni++)
                    rf_name[rf_ni] = (source->data)[rf_nstart + rf_ni];
                  (void)((lex = (r_peek.next_lex)));
                  (void)((expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
                  (void)(parser_parse_expr_into(arena, lex, source, &(expr_res_fi)));
                  if (!((expr_res_fi.ok))) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  lo_ref = (expr_res_fi.expr_ref);
                  (void)((lex = (expr_res_fi.next_lex)));
                  (void)(lexer_next_into(&(r), lex, source));
                  /*
                   * Range separator `..`:
                   * - TOKEN_DOTDOT (preferred), or
                   * - two TOKEN_DOT, or
                   * - single TOKEN_DOT when lexer already fused/skipped (product residual).
                   */
                  if ((((r.tok).kind) == token_TokenKind_TOKEN_DOTDOT)) {
                    (void)((lex = (r.next_lex)));
                  } else if ((((r.tok).kind) == token_TokenKind_TOKEN_DOT)) {
                    (void)((lex = (r.next_lex)));
                    (void)(lexer_next_into(&(r), lex, source));
                    if ((((r.tok).kind) == token_TokenKind_TOKEN_DOT)) {
                      (void)((lex = (r.next_lex)));
                    } else {
                      /* Single-DOT residual: r is first token of hi expr — restart lex at that token. */
                      int32_t run = 1;
                      if ((((r.tok).kind) == token_TokenKind_TOKEN_IDENT))
                        run = ((r.tok).ident_len);
                      else if ((((r.tok).kind) == token_TokenKind_TOKEN_INT))
                        run = 1; /* length recovered below via token_start if set */
                      if ((r.token_start) > 0) {
                        (void)((lex = (struct lexer_Lexer){ .pos = (r.token_start), .line = ((r.tok).line), .col = ((r.tok).col) }));
                      } else {
                        (void)((lex = (struct lexer_Lexer){ .pos = parser_lexer_pos_before_run(((r.next_lex).pos), run),
                            .line = ((r.tok).line), .col = ((r.tok).col) }));
                      }
                    }
                  } else {
                    (void)(parser_set_onefunc_fail(out, lex)); return;
                  }
                  (void)((expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
                  (void)(parser_parse_expr_into(arena, lex, source, &(expr_res_fc)));
                  if (!((expr_res_fc.ok))) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  hi_ref = (expr_res_fc.expr_ref);
                  (void)((lex = (expr_res_fc.next_lex)));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) !=83)) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  (void)((lex = (r.next_lex)));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) !=84)) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  (void)((lex = (r.next_lex)));
                  (void)((block_res_f = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
                  (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_f)));
                  if (!((block_res_f.ok))) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  i32ty = ast_ast_arena_type_alloc(arena);
                  if (i32ty > 0) {
                    struct ast_Type ti32 = ast_ast_arena_type_get(arena, i32ty);
                    ti32.kind = ast_TypeKind_TYPE_I32;
                    (void)(ast_ast_arena_type_set(arena, i32ty, ti32));
                  }
                  let_i = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out));
                  if (pipeline_onefunc_append_let(parser_onefunc_result_pool_ptr(out), rf_name, rf_nlen, 0, lo_ref, i32ty) < 0) {
                    (void)(parser_set_onefunc_fail(out, lex)); return;
                  }
                  (void)(((out->num_lets) = pipeline_onefunc_num_lets(parser_onefunc_result_pool_ptr(out))));
                  (void)(parser_onefunc_push_src_stmt(out, 1, let_i));
                  /* cond: i < hi ; step: i = i + 1  (ExprKind VAR=3 ADD=4 LT=16 ASSIGN=28) */
                  v1 = ast_ast_arena_expr_alloc(arena);
                  v2 = ast_ast_arena_expr_alloc(arena);
                  v3 = ast_ast_arena_expr_alloc(arena);
                  one_ref = ast_ast_arena_expr_alloc(arena);
                  lt_ref = ast_ast_arena_expr_alloc(arena);
                  add_ref = ast_ast_arena_expr_alloc(arena);
                  asg_ref = ast_ast_arena_expr_alloc(arena);
                  if (!(v1 && v2 && v3 && one_ref && lt_ref && add_ref && asg_ref)) {
                    (void)(parser_set_onefunc_fail(out, lex)); return;
                  }
                  ve = ast_ast_arena_expr_get(arena, v1);
                  ve.kind = 3; ve.var_name_len = rf_nlen;
                  for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                  for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                  ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                  ast_ast_arena_expr_set(arena, v1, ve);
                  ve = ast_ast_arena_expr_get(arena, v2);
                  ve.kind = 3; ve.var_name_len = rf_nlen;
                  for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                  for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                  ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                  ast_ast_arena_expr_set(arena, v2, ve);
                  ve = ast_ast_arena_expr_get(arena, v3);
                  ve.kind = 3; ve.var_name_len = rf_nlen;
                  for (rf_ni = 0; rf_ni < rf_nlen; rf_ni++) ve.var_name[rf_ni] = rf_name[rf_ni];
                  for (; rf_ni < 128; rf_ni++) ve.var_name[rf_ni] = 0;
                  ve.line = 0; ve.col = 0; ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                  ast_ast_arena_expr_set(arena, v3, ve);
                  ve = ast_ast_arena_expr_get(arena, one_ref);
                  ve.kind = 0; ve.int_val = 1; ve.line = 0; ve.col = 0;
                  ve.binop_left_ref = 0; ve.binop_right_ref = 0;
                  ast_ast_arena_expr_set(arena, one_ref, ve);
                  ve = ast_ast_arena_expr_get(arena, lt_ref);
                  ve.kind = 16; ve.binop_left_ref = v1; ve.binop_right_ref = hi_ref;
                  ve.line = 0; ve.col = 0; ve.int_val = 0;
                  ast_ast_arena_expr_set(arena, lt_ref, ve);
                  ve = ast_ast_arena_expr_get(arena, add_ref);
                  ve.kind = 4; ve.binop_left_ref = v2; ve.binop_right_ref = one_ref;
                  ve.line = 0; ve.col = 0; ve.int_val = 0;
                  ast_ast_arena_expr_set(arena, add_ref, ve);
                  ve = ast_ast_arena_expr_get(arena, asg_ref);
                  ve.kind = 28; ve.binop_left_ref = v3; ve.binop_right_ref = add_ref;
                  ve.line = 0; ve.col = 0; ve.int_val = 0;
                  ast_ast_arena_expr_set(arena, asg_ref, ve);
                  for_idx = pipeline_onefunc_append_for(parser_onefunc_result_pool_ptr(out), 0, lt_ref, asg_ref, (block_res_f.block_ref));
                  if (for_idx < 0) { (void)(parser_set_onefunc_fail(out, lex)); return; }
                  (void)(((impl_snap.num_for_loops) = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(out))));
                  (void)(parser_onefunc_push_src_stmt(out, 4, for_idx));
                  (void)((lex = (block_res_f.next_lex)));
                  (void)((stmt_tok_ready = 0));
                  range_for_done = 1;
                }
              }
              if (range_for_done) {
                continue;
              }
              (void)((expr_res_fi = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
              (void)(parser_parse_expr_into(arena, lex, source, &(expr_res_fi)));
              if (!((expr_res_fi.ok))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)((init_ref = (expr_res_fi.expr_ref)));
              (void)((lex = (expr_res_fi.next_lex)));
              (void)(lexer_next_into(&(r), lex, source));
            }
          }
          if (!(for_past_init_semi_fn)) {
            if ((((r.tok).kind) !=95)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((lex = (r.next_lex)));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if ((((r.tok).kind) !=95)) {
            (void)((expr_res_fc = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
            (void)(parser_parse_expr_into(arena, lex, source, &(expr_res_fc)));
            if (!((expr_res_fc.ok))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((for_cond_ref = (expr_res_fc.expr_ref)));
            (void)((lex = (expr_res_fc.next_lex)));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if ((((r.tok).kind) !=95)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=83)) {
            (void)((expr_res_fs = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex }));
            (void)(parser_parse_expr_into(arena, lex, source, &(expr_res_fs)));
            if (!((expr_res_fs.ok))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)((step_ref = (expr_res_fs.expr_ref)));
            (void)((lex = (expr_res_fs.next_lex)));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if ((((r.tok).kind) !=83)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=84)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (r.next_lex)));
          (void)((block_res_f = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_f)));
          if (!((block_res_f.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          if ((for_cond_ref ==0)) {
            (void)((cond_expr_ref = ast_ast_arena_expr_alloc(arena)));
            if ((cond_expr_ref !=0)) {
              struct ast_Expr ce = ast_ast_arena_expr_get(arena, cond_expr_ref);
              (void)(((ce.kind) = 2));
              (void)(((ce.int_val) = 1));
              (void)(((ce.line) = 0));
              (void)(((ce.col) = 0));
              (void)(parser_expr_set_common_zeros(&(ce)));
              (void)(ast_ast_arena_expr_set(arena, cond_expr_ref, ce));
              (void)((for_cond_ref = cond_expr_ref));
            }
          }
          (void)((for_idx = pipeline_onefunc_append_for(parser_onefunc_result_pool_ptr(out), init_ref, for_cond_ref, step_ref, (block_res_f.block_ref))));
          if ((for_idx < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((impl_snap.num_for_loops) = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(out))));
          (void)(parser_onefunc_push_src_stmt(out, 4, for_idx));
          (void)((lex = (block_res_f.next_lex)));
          (void)((stmt_tok_ready = 0));
          continue;
        }
        if ((((r.tok).kind) ==82)) {
          (void)((lex = parser_rewind_lex_for_lparen_control_stmt(lex, r, source)));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) ==18)) {
          /* wave371: mid-body/final match stmt (G.7 parse_match_into). */
          struct lexer_Lexer match_mid_lex = parser_lex_at_token_from_result(r);
          struct parser_ParseExprResult match_mid_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = match_mid_lex };
          int32_t match_ex_i = 0;
          (void)(parser_parse_match_into(arena, match_mid_lex, source, &(match_mid_res)));
          if (!((match_mid_res.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((lex = (match_mid_res.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
            struct lexer_LexerResult after_match_semi = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
            (void)(lexer_next_into(&(after_match_semi), lex, source));
            (void)((r = after_match_semi));
          }
          if ((((r.tok).kind) ==85)) {
            (void)(((impl_snap.has_final_expr) = 1));
            (void)(((impl_snap.has_explicit_return_kw) = 1));
            (void)((return_expr_ref_storage = (match_mid_res.expr_ref)));
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
            return;
          }
          (void)((match_ex_i = pipeline_onefunc_push_body_expr_stmt(parser_onefunc_result_pool_ptr(out), (match_mid_res.expr_ref))));
          if ((match_ex_i < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((out->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(out))));
          (void)(parser_onefunc_push_src_stmt(out, 2, match_ex_i));
          (void)((stmt_tok_ready = 1));
          continue;
        }
        if ((((r.tok).kind) ==4)) {
          struct lexer_Lexer if_start_fn = parser_lex_at_token_from_result(r);
          int32_t if_cref = 0;
          int32_t if_then_ref = 0;
          int32_t if_else_ref = 0;
          if (!(parser_parse_if_stmt_into(arena, if_start_fn, source, 0, &(if_cref), &(if_then_ref), &(if_else_ref), &(lex)))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          int32_t if_pool_idx = pipeline_onefunc_append_if(parser_onefunc_result_pool_ptr(out), if_cref, if_then_ref, if_else_ref);
          if ((if_pool_idx < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_onefunc_push_src_stmt(out, 5, if_pool_idx));
          (void)((stmt_tok_ready = 0));
          continue;
        }
        if ((((r.tok).kind) ==84)) {
          struct parser_ParseBlockResult block_res_bare_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex };
          int32_t bare_expr_fn = 0;
          int32_t bare_ex_fn = 0;
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)((block_res_bare_fn = (struct parser_ParseBlockResult){ .ok = 0, .block_ref = 0, .next_lex = lex }));
          (void)(parser_parse_block_into(arena, lex, source, ret_type_ref, &(block_res_bare_fn)));
          if (!((block_res_bare_fn.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((bare_expr_fn = parser_wrap_block_ref_as_expr(arena, (block_res_bare_fn.block_ref), ret_type_ref)));
          if ((bare_expr_fn ==0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)((bare_ex_fn = pipeline_onefunc_push_body_expr_stmt(parser_onefunc_result_pool_ptr(out), bare_expr_fn)));
          if ((bare_ex_fn < 0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((out->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(out))));
          (void)(parser_onefunc_push_src_stmt(out, 2, bare_ex_fn));
          (void)((lex = (block_res_bare_fn.next_lex)));
          (void)((stmt_tok_ready = 0));
          continue;
        }
        (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
        (void)((stmt_start = parser_lex_at_token_from_result(r)));
        (void)(parser_parse_expr_result_reset(&(expr_stmt_res), stmt_start));
        if ((((r.tok).kind) ==80)) {
          (void)(parser_parse_cond_expr_into(arena, stmt_start, source, &(expr_stmt_res)));
        } else {
          (void)(parser_parse_expr_into(arena, stmt_start, source, &(expr_stmt_res)));
        }
        if (!((expr_stmt_res.ok))) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)((lex = (expr_stmt_res.next_lex)));
        if ((parser_advance_past_stmt_semicolon_into(&(r), lex, source) ==0)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_result_ptr_into(&(lex), &(r)));
          struct lexer_LexerResult after_semi = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
          (void)(lexer_next_into(&(after_semi), lex, source));
          (void)((r = after_semi));
        }
        (void)((ex_i = pipeline_onefunc_push_body_expr_stmt(parser_onefunc_result_pool_ptr(out), (expr_stmt_res.expr_ref))));
        if ((ex_i < 0)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(((out->num_src_body_expr_stmts) = pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(out))));
        (void)(parser_onefunc_push_src_stmt(out, 2, ex_i));
        /* wave379: RETURN no longer ends loop after expr stmt */
        if ((((((r.tok).kind) ==85) || (((r.tok).kind) ==0)))) {
          break;
        }
        (void)((lex = parser_lex_at_token_from_result(r)));
        (void)((stmt_tok_ready = 1));
        continue;
      }
    } else {
      (void)(parser_set_onefunc_fail(out, lex));
      return;
    }
    if ((((r.tok).kind) ==85)) {
      (void)(parser_lex_from_next_into(&(lex), r));
      (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
      return;
    }
    (void)(((impl_snap.has_final_expr) = 1));
    if ((((r.tok).kind) ==18)) {
      (void)(((impl_snap.has_explicit_return_kw) = 1));
      struct lexer_Lexer match_tail_lex = parser_lex_at_token_from_result(r);
      struct parser_ParseExprResult match_tail_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = match_tail_lex };
      (void)(parser_parse_match_into(arena, match_tail_lex, source, &(match_tail_res)));
      if (!((match_tail_res.ok))) {
        (void)(parser_set_onefunc_fail(out, lex));
        return;
      }
      (void)((return_expr_ref_storage = (match_tail_res.expr_ref)));
      (void)((lex = (match_tail_res.next_lex)));
      (void)(lexer_next_into(&(r), lex, source));
      if ((((r.tok).kind) ==95)) {
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
      }
      if ((((r.tok).kind) !=85)) {
        (void)(parser_set_onefunc_fail(out, lex));
        return;
      }
      (void)(parser_lex_from_next_into(&(lex), r));
      (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
      return;
    }
    if ((((r.tok).kind) ==59)) {
      size_t subj_start = (r.token_start);
      if ((subj_start ==0)) {
        (void)((subj_start = parser_lexer_pos_before_run(((r.next_lex).pos), ((r.tok).ident_len))));
      }
      if (parser_match_kw_immediately_before(source, subj_start)) {
        (void)(((impl_snap.has_explicit_return_kw) = 1));
        struct lexer_Lexer match_subj_lex = (struct lexer_Lexer){ .pos = (subj_start - 6), .line = ((r.tok).line), .col = ((r.tok).col) };
        struct parser_ParseExprResult match_subj_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = match_subj_lex };
        (void)(parser_parse_match_into(arena, match_subj_lex, source, &(match_subj_res)));
        if (!((match_subj_res.ok))) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)((return_expr_ref_storage = (match_subj_res.expr_ref)));
        (void)((lex = (match_subj_res.next_lex)));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=85)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
        return;
      }
    }
    if ((((r.tok).kind) ==11)) {
      (void)(((impl_snap.has_explicit_return_kw) = 1));
      (void)(parser_lex_from_next_into(&(lex), r));
      (void)(lexer_next_into(&(r), lex, source));
      /* wave378 Cap residual pure: bare `return;` / `return }` (void return).
       * Nested parse_block already accepts empty operand; onefunc final path
       * required an expression and failed on TOKEN_SEMICOLON → XP003 / dropped
       * void functions. G.7: bare EXPR_RETURN (null unary_operand); typeck rejects
       * for non-void; codegen emits return; / void main return 0.
       * PLATFORM: SHARED — onefunc parse; pin same commit as parser.x. */
      if (((((r.tok).kind) ==95) || (((r.tok).kind) ==85))) {
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=85)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        {
          int32_t bare_ret = ast_ast_arena_expr_alloc(arena);
          if ((bare_ret ==0)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          struct ast_Expr bre = ast_ast_arena_expr_get(arena, bare_ret);
          (void)(((bre.kind) = ast_ExprKind_EXPR_RETURN));
          (void)(((bre.line) = 0));
          (void)(((bre.col) = 0));
          (void)(parser_expr_set_common_zeros(&(bre)));
          (void)(ast_ast_arena_expr_set(arena, bare_ret, bre));
          (void)((return_expr_ref_storage = bare_ret));
        }
        (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
        return;
      }
      if ((((r.tok).kind) ==18)) {
        struct lexer_Lexer match_ret_lex = parser_lex_at_token_from_result(r);
        struct parser_ParseExprResult match_ret_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = match_ret_lex };
        (void)(parser_parse_match_into(arena, match_ret_lex, source, &(match_ret_res)));
        if (!((match_ret_res.ok))) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)((return_expr_ref_storage = (match_ret_res.expr_ref)));
        (void)((lex = (match_ret_res.next_lex)));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=85)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
        return;
      }
      if ((!(return_type_is_bool) && (((r.tok).kind) !=4))) {
        struct lexer_Lexer rex_u_lex = parser_lex_at_token_from_result(r);
        struct parser_ParseExprResult rex_u_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = rex_u_lex };
        (void)(parser_parse_cond_expr_into(arena, rex_u_lex, source, &(rex_u_res)));
        if ((rex_u_res.ok)) {
          (void)((return_expr_ref_storage = (rex_u_res.expr_ref)));
          (void)((lex = (rex_u_res.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if ((((r.tok).kind) !=85)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
          return;
        }
      }
      if ((((r.tok).kind) ==4)) {
        struct lexer_Lexer if_lex = parser_lex_at_token_from_result(r);
        struct parser_ParseExprResult if_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = if_lex };
        (void)(parser_parse_if_expr_into(arena, if_lex, source, 0, &(if_res)));
        if ((if_res.ok)) {
          (void)((return_expr_ref_storage = (if_res.expr_ref)));
          (void)((lex = (if_res.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) ==95)) {
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
          }
          if ((((r.tok).kind) !=85)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
          return;
        }
        (void)((lex = if_lex));
        (void)(lexer_next_into(&(r), lex, source));
      }
      if ((return_type_is_bool && (((r.tok).kind) !=4))) {
        struct lexer_Lexer rex_lex = parser_lex_at_token_from_result(r);
        struct parser_ParseExprResult rex_out = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = rex_lex };
        (void)(parser_parse_cond_expr_into(arena, rex_lex, source, &(rex_out)));
        if (!((rex_out.ok))) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)((return_expr_ref_storage = (rex_out.expr_ref)));
        (void)((lex = (rex_out.next_lex)));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=85)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
        return;
      }
      if ((((r.tok).kind) ==4)) {
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) !=82)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        struct lexer_Lexer lex_cond_start = lex;
        (void)(lexer_next_into(&(r), lex, source));
        if (((((r.tok).kind) ==75) || (((r.tok).kind) ==76))) {
          (void)(((impl_snap.if_cond_true) = (((r.tok).kind) ==75)));
          (void)(((impl_snap.if_cond_expr_ref) = 0));
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        } else {
          struct parser_ParseExprResult cond_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = lex_cond_start };
          (void)(parser_parse_expr_into(arena, lex_cond_start, source, &(cond_res)));
          if (!((cond_res.ok))) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((impl_snap.if_cond_expr_ref) = (cond_res.expr_ref)));
          (void)(((impl_snap.if_cond_true) = 0));
          (void)((lex = (cond_res.next_lex)));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) ==83)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) ==84)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=80)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(((impl_snap.if_then_val) = ((r.tok).int_val)));
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==85)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=5)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==84)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        if ((((r.tok).kind) !=80)) {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
        (void)(((impl_snap.if_else_val) = ((r.tok).int_val)));
        (void)(((impl_snap.has_if_expr) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)(lexer_next_into(&(r), lex, source));
        if ((((r.tok).kind) ==85)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        }
        (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
        return;
      } else {
        if ((((r.tok).kind) ==97)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=80)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(((impl_snap.return_val) = ((r.tok).int_val)));
          (void)(((impl_snap.has_unary_neg) = 1));
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
        } else {
          if ((((r.tok).kind) ==80)) {
            /* wave305: full i64; plain return uses parser_alloc_int_lit (not return_val:i32). */
            int64_t ret_int_val = ((r.tok).int_val);
            size_t ret_int_start = (r.token_start);
            if ((ret_int_start ==0)) {
              (void)((ret_int_start = (((r.next_lex).pos) - 1)));
            }
            struct lexer_Lexer ret_int_lex = (struct lexer_Lexer){ .pos = ret_int_start, .line = (lex.line), .col = (lex.col) };
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
            if ((((r.tok).kind) ==128)) {
              struct parser_ParseExprResult ret_expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = ret_int_lex };
              (void)(parser_parse_expr_into(arena, ret_int_lex, source, &(ret_expr_res)));
              if (!((ret_expr_res.ok))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)((return_expr_ref_storage = (ret_expr_res.expr_ref)));
              (void)((lex = (ret_expr_res.next_lex)));
              if (!(parser_onefunc_finish_after_return_lex(out, &(impl_snap), source, lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              return;
            }
            if (((((r.tok).kind) !=95) && (((r.tok).kind) !=85))) {
              struct parser_ParseExprResult rex_add = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = ret_int_lex };
              (void)(parser_parse_expr_into(arena, ret_int_lex, source, &(rex_add)));
              if (!((rex_add.ok))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)((return_expr_ref_storage = (rex_add.expr_ref)));
              (void)((lex = (rex_add.next_lex)));
              if (!(parser_onefunc_finish_after_return_lex(out, &(impl_snap), source, lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              return;
            }
            (void)((return_expr_ref_storage = parser_alloc_int_lit(arena, ret_int_val)));
            if ((return_expr_ref_storage ==0)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(((impl_snap.return_val) = 0));
            if (!(parser_onefunc_finish_after_return_lex(out, &(impl_snap), source, lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage))) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            return;
          } else {
            if ((((r.tok).kind) !=59)) {
              struct lexer_Lexer rex_lex_ni = parser_lex_at_token_from_result(r);
              struct parser_ParseExprResult rex_out_ni = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = rex_lex_ni };
              (void)(parser_parse_expr_into(arena, rex_lex_ni, source, &(rex_out_ni)));
              if (!((rex_out_ni.ok))) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)((return_expr_ref_storage = (rex_out_ni.expr_ref)));
              (void)((lex = (rex_out_ni.next_lex)));
              (void)(lexer_next_into(&(r), lex, source));
              if ((((r.tok).kind) ==95)) {
                (void)(parser_lex_from_next_into(&(lex), r));
                (void)(lexer_next_into(&(r), lex, source));
              }
              if ((((r.tok).kind) !=85)) {
                (void)(parser_set_onefunc_fail(out, lex));
                return;
              }
              (void)(parser_lex_from_next_into(&(lex), r));
              (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
              return;
            }
            if ((((r.tok).kind) ==59)) {
              int32_t clen = ((r.tok).ident_len);
              if (((clen > 0) && (clen <=63))) {
                size_t cstart = (((r.next_lex).pos) - clen);
                (void)(parser_copy_slice_to_name64(source, cstart, clen, &(((impl_snap.call_callee_name))[0])));
                (void)(((impl_snap.call_callee_len) = clen));
                (void)(parser_lex_from_next_into(&(lex), r));
                (void)(lexer_next_into(&(r), lex, source));
                if (((((r.tok).kind) ==96) && ((out->num_params) >=2))) {
                  (void)(parser_lex_from_next_into(&(lex), r));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) ==59)) {
                    uint8_t * binop_pool = parser_onefunc_result_pool_ptr(out);
                    int left_ok = ((impl_snap.call_callee_len) ==pipeline_onefunc_param_name_len(binop_pool, 0));
                    if (left_ok) {
                      int32_t ii = 0;
                      while ((ii < (impl_snap.call_callee_len))) {
                        if ((((impl_snap.call_callee_name))[ii] !=pipeline_onefunc_param_name_byte_at(binop_pool, 0, ii))) {
                          (void)((left_ok = 0));
                        }
                        (void)((ii = (ii + 1)));
                      }
                    }
                    int right_ok = (((r.tok).ident_len) ==pipeline_onefunc_param_name_len(binop_pool, 1));
                    if ((left_ok && right_ok)) {
                      (void)(((impl_snap.has_binop) = 1));
                      (void)(((impl_snap.binop_left_param_idx) = 0));
                      (void)(((impl_snap.binop_right_param_idx) = 1));
                      (void)(((impl_snap.return_val) = 0));
                      (void)(parser_lex_from_next_into(&(lex), r));
                      (void)(lexer_next_into(&(r), lex, source));
                      if ((((r.tok).kind) ==95)) {
                        (void)(parser_lex_from_next_into(&(lex), r));
                        (void)(lexer_next_into(&(r), lex, source));
                        if ((((r.tok).kind) ==85)) {
                          (void)(parser_lex_from_next_into(&(lex), r));
                          (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                          return;
                        }
                      }
                    }
                  }
                }
                if (((((r.tok).kind) ==84) && parser_match_kw_immediately_before(source, cstart))) {
                  size_t match_back = (cstart - 6);
                  struct lexer_Lexer match_lex_fix = (struct lexer_Lexer){ .pos = match_back, .line = ((r.tok).line), .col = ((r.tok).col) };
                  struct parser_ParseExprResult match_fix_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = match_lex_fix };
                  (void)(parser_parse_match_into(arena, match_lex_fix, source, &(match_fix_res)));
                  if (!((match_fix_res.ok))) {
                    (void)(parser_set_onefunc_fail(out, lex));
                    return;
                  }
                  (void)((return_expr_ref_storage = (match_fix_res.expr_ref)));
                  (void)((lex = (match_fix_res.next_lex)));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) ==95)) {
                    (void)(parser_lex_from_next_into(&(lex), r));
                    (void)(lexer_next_into(&(r), lex, source));
                  }
                  if ((((r.tok).kind) !=85)) {
                    (void)(parser_set_onefunc_fail(out, lex));
                    return;
                  }
                  (void)(parser_lex_from_next_into(&(lex), r));
                  (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                  return;
                }
                if (((((r.tok).kind) ==85) || (((r.tok).kind) ==95))) {
                  (void)(((impl_snap.has_call_expr) = 0));
                  (void)(((impl_snap.return_val) = 0));
                  (void)(parser_onefunc_snap_set_return_path(&(impl_snap), 0, (impl_snap.call_callee_name), (impl_snap.call_callee_len), 0));
                  if ((((r.tok).kind) ==85)) {
                    (void)(parser_lex_from_next_into(&(lex), r));
                    (void)(lexer_next_into(&(r), lex, source));
                  } else {
                    (void)(parser_lex_from_next_into(&(lex), r));
                    (void)(lexer_next_into(&(r), lex, source));
                    if ((((r.tok).kind) !=85)) {
                      (void)(parser_set_onefunc_fail(out, lex));
                      return;
                    }
                    (void)(parser_lex_from_next_into(&(lex), r));
                    (void)(lexer_next_into(&(r), lex, source));
                  }
                  (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                  return;
                }
                if ((((r.tok).kind) ==82)) {
                  struct lexer_Lexer ret_expr_lex = (struct lexer_Lexer){ .pos = cstart, .line = 1, .col = 1 };
                  struct parser_ParseExprResult ret_expr_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = ret_expr_lex };
                  (void)(parser_parse_expr_into(arena, ret_expr_lex, source, &(ret_expr_res)));
                  if (!((ret_expr_res.ok))) {
                    (void)(parser_set_onefunc_fail(out, lex));
                    return;
                  }
                  (void)((return_expr_ref_storage = (ret_expr_res.expr_ref)));
                  (void)(((impl_snap.has_call_expr) = 0));
                  (void)(((impl_snap.call_callee_len) = 0));
                  (void)(((impl_snap.call_num_args) = 0));
                  (void)((lex = (ret_expr_res.next_lex)));
                  (void)(lexer_next_into(&(r), lex, source));
                  if ((((r.tok).kind) ==95)) {
                    (void)(parser_lex_from_next_into(&(lex), r));
                    (void)(lexer_next_into(&(r), lex, source));
                  }
                  if ((((r.tok).kind) !=85)) {
                    (void)(parser_set_onefunc_fail(out, lex));
                    return;
                  }
                  (void)(parser_lex_from_next_into(&(lex), r));
                  (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                  return;
                }
                struct lexer_Lexer ret_expr_lex_member = (struct lexer_Lexer){ .pos = cstart, .line = 1, .col = 1 };
                struct parser_ParseExprResult ret_expr_res_member = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = ret_expr_lex_member };
                (void)(parser_parse_expr_into(arena, ret_expr_lex_member, source, &(ret_expr_res_member)));
                if (!((ret_expr_res_member.ok))) {
                  (void)(parser_set_onefunc_fail(out, lex));
                  return;
                }
                (void)((return_expr_ref_storage = (ret_expr_res_member.expr_ref)));
                (void)(((impl_snap.has_call_expr) = 0));
                (void)(((impl_snap.call_callee_len) = 0));
                (void)(((impl_snap.call_num_args) = 0));
                (void)((lex = (ret_expr_res_member.next_lex)));
                (void)(lexer_next_into(&(r), lex, source));
                if ((((r.tok).kind) ==95)) {
                  (void)(parser_lex_from_next_into(&(lex), r));
                  (void)(lexer_next_into(&(r), lex, source));
                }
                if ((((r.tok).kind) !=85)) {
                  (void)(parser_set_onefunc_fail(out, lex));
                  return;
                }
                (void)(parser_lex_from_next_into(&(lex), r));
                (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                return;
              } else {
                struct lexer_Lexer ret_id_badlen_lex = parser_lex_at_token_from_result(r);
                struct parser_ParseExprResult ret_id_badlen_res = (struct parser_ParseExprResult){ .ok = 0, .expr_ref = 0, .next_lex = ret_id_badlen_lex };
                (void)(parser_parse_expr_into(arena, ret_id_badlen_lex, source, &(ret_id_badlen_res)));
                if (!((ret_id_badlen_res.ok))) {
                  (void)(parser_set_onefunc_fail(out, lex));
                  return;
                }
                (void)((return_expr_ref_storage = (ret_id_badlen_res.expr_ref)));
                (void)(((impl_snap.has_call_expr) = 0));
                (void)(((impl_snap.call_callee_len) = 0));
                (void)(((impl_snap.call_num_args) = 0));
                (void)((lex = (ret_id_badlen_res.next_lex)));
                (void)(lexer_next_into(&(r), lex, source));
                if ((((r.tok).kind) ==95)) {
                  (void)(parser_lex_from_next_into(&(lex), r));
                  (void)(lexer_next_into(&(r), lex, source));
                }
                if ((((r.tok).kind) !=85)) {
                  (void)(parser_set_onefunc_fail(out, lex));
                  return;
                }
                (void)(parser_lex_from_next_into(&(lex), r));
                (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
                return;
              }
            }
            while ((1 ==1)) {
              if (((((r.tok).kind) ==95) || (((r.tok).kind) ==0))) {
                break;
              }
              (void)(parser_lex_from_next_into(&(lex), r));
              (void)(lexer_next_into(&(r), lex, source));
            }
            if ((((r.tok).kind) !=95)) {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_lex_from_next_into(&(lex), r));
            (void)(lexer_next_into(&(r), lex, source));
            (void)(((impl_snap.return_val) = 0));
            if ((((r.tok).kind) ==85)) {
              (void)(parser_lex_from_next_into(&(lex), r));
            } else {
              (void)(parser_set_onefunc_fail(out, lex));
              return;
            }
            (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
            return;
          }
        }
      }
      if ((((r.tok).kind) ==85)) {
        (void)(parser_lex_from_next_into(&(lex), r));
      } else {
        if ((((r.tok).kind) ==95)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          (void)(lexer_next_into(&(r), lex, source));
          if ((((r.tok).kind) !=85)) {
            (void)(parser_set_onefunc_fail(out, lex));
            return;
          }
          (void)(parser_lex_from_next_into(&(lex), r));
        } else {
          (void)(parser_set_onefunc_fail(out, lex));
          return;
        }
      }
      (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
      return;
    } else {
      (void)((lex = parser_skip_balanced_braces(lex, source)));
      (void)(parser_onefunc_finish_impl_to_out(out, &(impl_snap), lex, &((dummy_name)[0]), (func_name_len_storage)[0], return_expr_ref_storage));
      return;
    }
  }
}
int32_t parser_import_path_dot_segment_len(enum token_TokenKind kind, int32_t ident_len) {
  {
    if (((kind ==59) && (ident_len > 0))) {
      return ident_len;
    }
    if ((kind ==60)) {
      return 3;
    }
    int32_t ko = ((int32_t)(kind));
    if ((ko ==29)) {
      return 5;
    }
    return -(1);
  }
}
extern void parser_import_path_dot_segment_copy_glue(struct xlang_slice_uint8_t * source, size_t token_start, int32_t seg_len, uint8_t * path_buf, int32_t path_len);
void parser_import_path_dot_segment_copy(struct xlang_slice_uint8_t * source, size_t token_start, int32_t seg_len, uint8_t * path_buf, int32_t path_len) {
  {
    int32_t i = 0;
    while ((i < seg_len)) {
      if (((token_start + ((size_t)(i))) < (source->length))) {
        (void)(((path_buf)[(path_len + i)] = (source)->data[(token_start + ((size_t)(i)))]));
      }
      (void)((i = (i + 1)));
    }
  }
}
void parser_import_path_dot_segment_copy_buf(uint8_t * data, int32_t len, size_t token_start, int32_t seg_len, uint8_t * path_buf, int32_t path_len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_import_path_dot_segment_copy(&(slice), token_start, seg_len, path_buf, path_len));
  }
}
void parser_parse_into_init(struct ast_Module * module, struct ast_ASTArena * arena) {
  (void)(ast_ast_arena_init(arena));
  (void)(ast_pool_module_reset(module));
  (void)(ast_pool_arena_reset(arena));
  (void)(parser_onefunc_result_layout_prime());
  (void)(parser_onefunc_result_layout_prime_b());
  (void)(parser_onefunc_result_layout_prime_c());
  (void)(parser_onefunc_result_layout_prime_d());
  (void)(parser_onefunc_result_layout_prime_d_b());
  (void)(parser_onefunc_result_layout_prime_e());
  (void)(parser_onefunc_result_layout_prime_f());
  (void)(parser_pipeline_module_reset_parse_counters(module));
  (void)(pipeline_parser_set_match_module(module));
}
extern struct lexer_Lexer parser_skip_imports_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_imports(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_imports_glue(lex, source);
}
struct lexer_Lexer parser_skip_imports_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_imports(lex, &(slice));
  }
}
extern void parser_collect_imports_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct ast_Module * module, struct parser_CollectImportsResult * out);
void parser_collect_imports(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct ast_Module * module, struct parser_CollectImportsResult * out) {
  (void)(parser_collect_imports_glue(lex, source, module, out));
}
void parser_collect_imports_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, struct ast_Module * module, struct parser_CollectImportsResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_collect_imports(lex, &(slice), module, out));
  }
}
extern void parser_skip_one_struct_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_struct_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_struct_into_glue(out, lex, source));
}
extern struct lexer_Lexer parser_skip_one_struct_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_struct(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_struct_glue(lex, source);
}
extern int32_t parser_module_try_register_enum_name_glue(struct ast_Module * module, uint8_t * name, int32_t name_len);
int32_t parser_module_try_register_enum_name(struct ast_Module * module, uint8_t * name, int32_t name_len) {
  {
    if (((((module ==((struct ast_Module *)(0))) || (name ==((uint8_t *)(0)))) || (name_len <=0)) || (name_len > 127))) {
      return -(1);
    }
    int32_t ei = 0;
    while ((ei < (module->num_module_enums))) {
      if ((pipeline_module_enum_name_len(module, ei) ==name_len)) {
        int eq = 1;
        int32_t j = 0;
        while ((j < name_len)) {
          if ((pipeline_module_enum_name_byte_at(module, ei, j) !=(name)[j])) {
            (void)((eq = 0));
            break;
          }
          (void)((j = (j + 1)));
        }
        if (eq) {
          return ei;
        }
      }
      (void)((ei = (ei + 1)));
    }
    int32_t slot = pipeline_module_enum_alloc(module);
    if ((slot < 0)) {
      return -(1);
    }
    (void)(pipeline_module_enum_set_name(module, slot, name, name_len));
    return slot;
  }
  return 0;
}
extern void parser_module_append_enum_variants_and_skip_body_into_glue(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_module_append_enum_variants_and_skip_body_into(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_module_append_enum_variants_and_skip_body_into_glue(module, enum_idx, out, lex, source));
}
void parser_module_append_enum_variants_and_skip_body_into_buf(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    int32_t depth = 1;
    size_t slen = ((size_t)(len));
    while ((depth > 0)) {
      struct lexer_LexerResult r = lexer_next_buf(lex, data, len);
      if ((((r.tok).kind) ==85)) {
        (void)((depth = (depth - 1)));
        if ((depth ==0)) {
          (void)(parser_lex_from_next_into(&(lex), r));
          break;
        }
      } else {
        if ((((r.tok).kind) ==84)) {
          (void)((depth = (depth + 1)));
        } else {
          if ((((depth ==1) && (enum_idx >=0)) && (((r.tok).kind) ==59))) {
            int32_t vlen = ((r.tok).ident_len);
            if ((vlen > 127)) {
              (void)((vlen = 127));
            }
            size_t vstart = (r.token_start);
            uint8_t vb[128] = {};
            int32_t nk = 0;
            while (((nk < vlen) && (nk < 128))) {
              size_t ix = (vstart + ((size_t)(nk)));
              if ((ix >=slen)) {
                break;
              }
              (void)(((vb)[nk] = (data)[ix]));
              (void)((nk = (nk + 1)));
            }
            if (((nk ==vlen) && (vlen > 0))) {
              (void)(pipeline_module_enum_append_variant(module, enum_idx, &((vb)[0]), vlen));
            }
          }
        }
      }
      (void)(parser_lex_from_next_into(&(lex), r));
    }
    (void)(((out->pos) = (lex.pos)));
    (void)(((out->line) = (lex.line)));
    (void)(((out->col) = (lex.col)));
  }
}
extern void parser_skip_one_enum_register_into_glue(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_enum_register_into(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_enum_register_into_glue(module, out, lex, source));
}
void parser_skip_one_enum_register_into_buf(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_enum_register_into(module, out, lex, &(slice)));
  }
}
void parser_skip_one_enum_register_buf(struct ast_Module * module, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  (void)(parser_skip_one_enum_register_into_buf(module, out, lex, data, len));
}
extern void parser_skip_one_enum_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_enum_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_enum_into_glue(out, lex, source));
}
extern struct lexer_Lexer parser_skip_one_enum_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_enum(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_enum_glue(lex, source);
}
extern void parser_skip_one_trait_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_trait_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_trait_into_glue(out, lex, source));
}
extern struct lexer_Lexer parser_skip_one_trait_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_trait(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_trait_glue(lex, source);
}
extern void parser_skip_one_impl_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_impl_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_impl_into_glue(out, lex, source));
}
extern struct lexer_Lexer parser_skip_one_impl_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_impl(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_impl_glue(lex, source);
}
void parser_skip_one_enum_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_enum_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_enum_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_enum(lex, &(slice));
  }
}
void parser_skip_one_trait_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_trait_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_trait_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_trait(lex, &(slice));
  }
}
void parser_skip_one_impl_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_impl_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_impl_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_impl(lex, &(slice));
  }
}
extern void parser_skip_one_extern_into_glue(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_skip_one_extern_into(struct lexer_Lexer * out, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_skip_one_extern_into_glue(out, lex, source));
}
extern struct lexer_Lexer parser_skip_one_extern_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct lexer_Lexer parser_skip_one_extern(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_skip_one_extern_glue(lex, source);
}
uint8_t * parser_extern_parse_pool_ptr(struct parser_ExternParseResult * res) {
  return ((uint8_t *)(res));
}
extern void parser_write_extern_params_to_pools_glue(struct ast_ASTArena * arena, struct ast_Module * module, int32_t func_ref, int32_t fi, struct parser_ExternParseResult * res);
void parser_write_extern_params_to_pools(struct ast_ASTArena * arena, struct ast_Module * module, int32_t func_ref, int32_t fi, struct parser_ExternParseResult * res) {
  {
    uint8_t * pool = parser_extern_parse_pool_ptr(res);
    int32_t p = 0;
    while ((p < (res->num_params))) {
      uint8_t pname32[128] = {};
      (void)(pipeline_onefunc_param_name_copy32(pool, p, &((pname32)[0])));
      int32_t plen = pipeline_onefunc_param_name_len(pool, p);
      int32_t pty = pipeline_onefunc_param_type_ref(pool, p);
      (void)(pipeline_arena_func_param_write(arena, func_ref, p, &((pname32)[0]), plen, pty));
      (void)(pipeline_module_func_param_write(module, fi, p, &((pname32)[0]), plen, pty));
      (void)((p = (p + 1)));
    }
  }
}
void parser_extern_parse_set_fail(struct parser_ExternParseResult * out, struct lexer_Lexer lex) {
  {
    uint8_t empty64[128] = {};
    (void)(((out->next_lex) = lex));
    (void)(((out->name_len) = -(1)));
    (void)(((out->return_ty_ref) = 0));
    (void)(((out->num_params) = 0));
    int32_t ni = 0;
    while ((ni < 128)) {
      (void)((((out->name))[ni] = (empty64)[ni]));
      (void)((ni = (ni + 1)));
    }
  }
}
extern void parser_parse_one_extern_skip_into_glue(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_parse_one_extern_skip_into(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_parse_one_extern_skip_into_glue(out, arena, lex, source));
}
void parser_parse_one_extern_skip_into_buf(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_one_extern_skip_into(out, arena, lex, &(slice)));
  }
}
int32_t parser_module_register_arena_func(struct ast_Module * module, int32_t func_ref, struct ast_Func f) {
  {
    int32_t fi = pipeline_module_func_alloc_slot(module);
    if ((fi < 0)) {
      return -(1);
    }
    (void)(pipeline_module_func_name_write(module, fi, &(((f.name))[0]), (f.name_len)));
    (void)(pipeline_module_func_set_num_params(module, fi, (f.num_params)));
    (void)(pipeline_module_func_set_num_generic_params(module, fi, (f.num_generic_params)));
    (void)(pipeline_module_func_set_return_type(module, fi, (f.return_type_ref)));
    (void)(pipeline_module_func_set_body_ref(module, fi, (f.body_ref)));
    (void)(pipeline_module_func_set_body_expr_ref(module, fi, (f.body_expr_ref)));
    (void)(pipeline_module_func_set_is_extern(module, fi, (f.is_extern)));
    (void)(pipeline_module_func_set_is_async(module, fi, (f.is_async)));
    /* Cap 10.7.1: Func.is_variadic → module slot (≡ parser.x). */
    (void)(pipeline_module_func_set_is_variadic(module, fi, (f.is_variadic)));
    (void)(pipeline_module_func_set_is_export(module, fi, (module->pending_export)));
    (void)(((module->pending_export) = 0));
    (void)(pipeline_module_func_set_is_used(module, fi, (module->pending_used)));
    (void)(((module->pending_used) = 0));
    (void)(pipeline_module_func_set_is_naked(module, fi, (module->pending_naked)));
    (void)(((module->pending_naked) = 0));
    (void)(pipeline_module_func_set_is_entry(module, fi, (module->pending_entry)));
    (void)(((module->pending_entry) = 0));
    (void)(pipeline_module_func_set_is_no_mangle(module, fi, (module->pending_no_mangle)));
    (void)(((module->pending_no_mangle) = 0));
    (void)(pipeline_module_func_set_is_interrupt(module, fi, (module->pending_interrupt)));
    (void)(((module->pending_interrupt) = 0));
    (void)(pipeline_module_func_ref_set(module, fi, func_ref));
    return fi;
  }
  return 0;
}
extern void parser_parse_one_extern_and_add_into_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out);
void parser_parse_one_extern_and_add_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * lex_out) {
  (void)(parser_parse_one_extern_and_add_into_glue(arena, module, lex, source, lex_out));
}
void parser_skip_one_extern_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_extern_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_extern_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_extern(lex, &(slice));
  }
}
extern void parser_parse_one_extern_and_add_into_buf_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out);
void parser_parse_one_extern_and_add_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out) {
  (void)(parser_parse_one_extern_and_add_into_buf_glue(arena, module, lex, data, len, lex_out));
}
extern void parser_lex_from_try_skip_into_glue(struct lexer_Lexer * out, struct parser_TrySkipAllowResult t);
void parser_lex_from_try_skip_into(struct lexer_Lexer * out, struct parser_TrySkipAllowResult t) {
  (void)(parser_lex_from_try_skip_into_glue(out, t));
}
extern void parser_lex_from_library_into_glue(struct lexer_Lexer * out, struct parser_LibraryParseResult lib);
void parser_lex_from_library_into(struct lexer_Lexer * out, struct parser_LibraryParseResult lib) {
  (void)(parser_lex_from_library_into_glue(out, lib));
}
extern struct lexer_Lexer parser_lex_from_try_skip_glue(struct parser_TrySkipAllowResult t);
struct lexer_Lexer parser_lex_from_try_skip(struct parser_TrySkipAllowResult t) {
  return parser_lex_from_try_skip_glue(t);
}
extern struct lexer_Lexer parser_lex_from_library_glue(struct parser_LibraryParseResult lib);
struct lexer_Lexer parser_lex_from_library(struct parser_LibraryParseResult lib) {
  return parser_lex_from_library_glue(lib);
}
extern int parser_parse_one_function_library_scan_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_LibraryParseScanResult * result);
int parser_parse_one_function_library_scan(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_LibraryParseScanResult * result) {
  return parser_parse_one_function_library_scan_glue(lex, source, result);
  return 0;
}
extern int parser_struct_layout_name_exists_arr_glue(struct ast_Module * module, uint8_t * nm, int32_t nlen);
int parser_struct_layout_name_exists_arr(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  {
    int32_t k = 0;
    while ((k < (module->num_struct_layouts))) {
      if (((pipeline_module_struct_layout_name_len(module, k) ==nlen) && (nlen > 0))) {
        int32_t ii = 0;
        int same = 1;
        while (((ii < nlen) && (ii < 128))) {
          if ((pipeline_module_struct_layout_name_byte_at(module, k, ii) !=(nm)[ii])) {
            (void)((same = 0));
          }
          (void)((ii = (ii + 1)));
        }
        if (same) {
          return 1;
        }
      }
      (void)((k = (k + 1)));
    }
    return 0;
  }
  return 0;
}
extern int32_t parser_struct_layout_first_name_match_idx_glue(struct ast_Module * module, uint8_t * nm, int32_t nlen);
int32_t parser_struct_layout_first_name_match_idx(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  {
    int32_t k = 0;
    while ((k < (module->num_struct_layouts))) {
      if (((pipeline_module_struct_layout_name_len(module, k) ==nlen) && (nlen > 0))) {
        int32_t ii = 0;
        int same = 1;
        while (((ii < nlen) && (ii < 128))) {
          if ((pipeline_module_struct_layout_name_byte_at(module, k, ii) !=(nm)[ii])) {
            (void)((same = 0));
          }
          (void)((ii = (ii + 1)));
        }
        if (same) {
          return k;
        }
      }
      (void)((k = (k + 1)));
    }
    return -(1);
  }
  return 0;
}
extern int32_t parser_struct_layout_placeholder_idx_glue(struct ast_Module * module, uint8_t * nm, int32_t nlen);
int32_t parser_struct_layout_placeholder_idx(struct ast_Module * module, uint8_t * nm, int32_t nlen) {
  {
    int32_t k = 0;
    while ((k < (module->num_struct_layouts))) {
      if (((pipeline_module_struct_layout_name_len(module, k) ==nlen) && (nlen > 0))) {
        int32_t ii = 0;
        int same = 1;
        while (((ii < nlen) && (ii < 128))) {
          if ((pipeline_module_struct_layout_name_byte_at(module, k, ii) !=(nm)[ii])) {
            (void)((same = 0));
          }
          (void)((ii = (ii + 1)));
        }
        if (same) {
          int32_t nf = pipeline_module_struct_layout_num_fields(module, k);
          if ((nf ==0)) {
            return k;
          }
          if (((nf ==1) && (pipeline_module_struct_layout_field_name_len(module, k, 0) ==0))) {
            return k;
          }
          if (((nf ==1) && (pipeline_module_struct_layout_field_type_ref(module, k, 0) ==0))) {
            return k;
          }
        }
      }
      (void)((k = (k + 1)));
    }
    return -(1);
  }
  return 0;
}
extern struct parser_LibraryParseResult parser_parse_one_function_library_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct parser_LibraryParseResult parser_parse_one_function_library(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_parse_one_function_library_glue(arena, module, lex, source);
}
struct parser_LibraryParseResult parser_parse_one_function_library_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_one_function_library(arena, module, lex, &(slice));
  }
}
extern struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow_glue(struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source);
struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow(struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source) {
  return parser_parse_into_try_skip_allow_glue(lex, r, source);
}
struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow_buf(struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_into_try_skip_allow(lex, r, &(slice));
  }
}
extern struct parser_TrySkipAllowResult parser_try_skip_allow_padding_struct_glue(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
struct parser_TrySkipAllowResult parser_try_skip_allow_padding_struct(struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  return parser_try_skip_allow_padding_struct_glue(lex, source);
}
struct parser_TrySkipAllowResult parser_try_skip_allow_padding_struct_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_try_skip_allow_padding_struct(lex, &(slice));
  }
}
void parser_skip_one_struct_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_one_struct_into(out, lex, &(slice)));
  }
}
struct lexer_Lexer parser_skip_one_struct_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_skip_one_struct(lex, &(slice));
  }
}
extern int32_t parser_consume_qualified_type_ident_name_glue(struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r, uint8_t * out, int32_t * out_len);
int32_t parser_consume_qualified_type_ident_name(struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r, uint8_t * out, int32_t * out_len) {
  return parser_consume_qualified_type_ident_name_glue(source, r, out, out_len);
  return 0;
}
int32_t parser_consume_qualified_type_ident_name_buf(uint8_t * data, int32_t len, struct lexer_LexerResult * r, uint8_t * out, int32_t * out_len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_consume_qualified_type_ident_name(&(slice), r, out, out_len);
  }
  return 0;
}
int parser_is_pointee_type_token(enum token_TokenKind kind) {
  if ((kind ==59)) {
    return 1;
  }
  if ((((kind ==60) || (kind ==65)) || (kind ==61))) {
    return 1;
  }
  if ((((kind ==62) || (kind ==63)) || (kind ==64))) {
    return 1;
  }
  if ((((kind ==66) || (kind ==67)) || (kind ==79))) {
    return 1;
  }
  if (((kind ==77) || (kind ==78))) {
    return 1;
  }
  return 0;
}
extern int32_t parser_alloc_pointee_type_ref_from_tok_glue(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r);
int32_t parser_alloc_pointee_type_ref_from_tok(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult * r) {
  return parser_alloc_pointee_type_ref_from_tok_glue(arena, source, r);
  return 0;
}
extern int32_t parser_parser_alloc_vector_type_ref_glue(struct ast_ASTArena * arena, int32_t elem_ord, int32_t lanes);
int32_t parser_alloc_vector_type_ref(struct ast_ASTArena * arena, int32_t elem_ord, int32_t lanes) {
  {
    int32_t elem_tr_v = pipeline_type_ensure_by_kind_ord(arena, elem_ord);
    int32_t vec_ref = 0;
    if ((elem_tr_v ==0)) {
      return 0;
    }
    (void)((vec_ref = ast_ast_arena_type_alloc(arena)));
    if ((vec_ref !=0)) {
      struct ast_Type tv = ast_ast_arena_type_get(arena, vec_ref);
      (void)(((tv.kind) = 13));
      (void)(((tv.elem_type_ref) = elem_tr_v));
      (void)(((tv.array_size) = lanes));
      (void)(((tv.name_len) = 0));
      (void)(ast_ast_arena_type_set(arena, vec_ref, tv));
    }
    return vec_ref;
  }
  return 0;
}
extern int32_t parser_parser_vector_type_ref_from_ident_spelling_glue(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult r);
int32_t parser_vector_type_ref_from_ident_spelling(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source, struct lexer_LexerResult r) {
  return parser_parser_vector_type_ref_from_ident_spelling_glue(arena, source, r);
  return 0;
}
extern int32_t parser_parse_struct_record_layout_into_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex, int32_t allow_pad, int32_t force_soa, int32_t repr_compat);
int32_t parser_parse_struct_record_layout_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct lexer_Lexer * out_lex, int32_t allow_pad, int32_t force_soa, int32_t repr_compat) {
  return parser_parse_struct_record_layout_into_glue(arena, module, lex, source, out_lex, allow_pad, force_soa, repr_compat);
  return 0;
}
extern void parser_parse_one_function_buf_into_glue(struct parser_OneFuncResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len);
void parser_parse_one_function_buf_into(struct parser_OneFuncResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  (void)(parser_parse_one_function_buf_into_glue(out, arena, lex, data, len));
}
extern void parser_parse_one_function_library_into_glue(struct parser_LibraryParseResult * out, struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source);
void parser_parse_one_function_library_into(struct parser_LibraryParseResult * out, struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source) {
  (void)(parser_parse_one_function_library_into_glue(out, arena, module, lex, source));
}
void parser_parse_one_function_library_into_buf(struct parser_LibraryParseResult * out, struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_one_function_library_into(out, arena, module, lex, &(slice)));
  }
}
extern void parser_parse_into_try_skip_allow_into_glue(struct parser_TrySkipAllowResult * out, struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source);
void parser_parse_into_try_skip_allow_into(struct parser_TrySkipAllowResult * out, struct lexer_Lexer lex, struct lexer_LexerResult r, struct xlang_slice_uint8_t * source) {
  (void)(parser_parse_into_try_skip_allow_into_glue(out, lex, r, source));
}
void parser_parse_into_try_skip_allow_into_buf(struct parser_TrySkipAllowResult * out, struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_into_try_skip_allow_into(out, lex, r, &(slice)));
  }
}
struct parser_ParseIntoResult parser_parse_into(struct ast_ASTArena * arena, struct ast_Module * module, struct xlang_slice_uint8_t * source) {
  {
    /* wave269: clear L001 sticky before scanning this source buffer. */
    lexer_unclosed_block_comment_reset();
    lexer_unclosed_string_reset();
    lexer_illegal_char_reset();
    lexer_incomplete_hex_reset();
    lexer_incomplete_exp_reset();
    lexer_incomplete_bin_reset();
    lexer_incomplete_oct_reset();
    lexer_invalid_digit_sep_reset();
    lexer_invalid_type_suffix_reset();
    lexer_invalid_escape_reset();
  lexer_string_lit_overflow_reset();
  lexer_ident_too_long_reset();
    /* wave421/wave425: trait registry + stash arena for return type kind checks. */
    {
      extern void xlang_trait_reg_reset_c(void *arena);
      xlang_trait_reg_reset_c((void *)arena);
    }
    struct lexer_Lexer lex = lexer_init();
    int32_t main_idx = -(1);
    /* skip_one_impl leaves the lexer inside `{...}`; nest counts those bodies
     * so the matching `}` is an impl closer, not unexpected junk. */
    int32_t impl_body_depth = 0;
    struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
    (void)(parser_collect_imports(lex, source, module, &(import_res)));
    (void)(parser_copy_lex_from_import_into(&(lex), import_res));
    int32_t loop_count = 0;
    while ((1 ==1)) {
      if ((loop_count >=131072)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1003) };
      }
      (void)((loop_count = (loop_count + 1)));
      struct lexer_Lexer iter_start = lex;
      struct lexer_LexerResult r = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
      struct lexer_Lexer current_tok_lex = lex;
      (void)(lexer_next_into(&(r), lex, source));
      (void)(parser_lex_from_next_into(&(lex), r));
      int32_t func_is_async_storage[1] = {};
      (void)(((func_is_async_storage)[0] = 0));
      if ((((r.tok).kind) ==55)) {
        (void)(((func_is_async_storage)[0] = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)((current_tok_lex = lex));
        (void)(lexer_next_into(&(r), lex, source));
        (void)(parser_lex_from_next_into(&(lex), r));
      }
      if ((((r.tok).kind) ==23)) {
        (void)(((module->pending_soa_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==24)) {
        if ((((r.tok).int_val) ==0)) {
          (void)(((module->pending_cfg_skip) = 1));
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==25)) {
        (void)(((module->pending_repr_c_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==26)) {
        (void)(((module->pending_repr_compatible_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==27)) {
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==31)) {
        (void)(((module->pending_used) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==29)) {
        (void)(((module->pending_naked) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==30)) {
        (void)(((module->pending_entry) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==32)) {
        (void)(((module->pending_no_mangle) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==35)) {
        (void)(((module->pending_interrupt) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==131)) {
        (void)(((module->pending_export) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if (((module->pending_cfg_skip) !=0)) {
        if ((((r.tok).kind) ==19)) {
          (void)(parser_skip_one_struct_into(&(lex), iter_start, source));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==3)) {
          (void)(parser_skip_one_top_level_const_into(&(lex), iter_start, source));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==2)) {
          (void)(parser_skip_one_top_level_let_into(&(lex), iter_start, source));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((((r.tok).kind) ==1) || ((func_is_async_storage)[0] !=0)) || (((r.tok).kind) ==54))) {
          (void)(parser_skip_one_function_full_into(&(lex), iter_start, source));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          (void)(((func_is_async_storage)[0] = 0));
          if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        (void)(({   struct parser_TrySkipAllowResult try_cfg_allow = (struct parser_TrySkipAllowResult){ .lex = lex, .skipped = 0, ._pad = { 0 } };
  (void)(parser_parse_into_try_skip_allow_into(&(try_cfg_allow), lex, r, source));
  if (((try_cfg_allow.skipped) !=0)) {
    (void)(parser_lex_from_try_skip_into(&(lex), try_cfg_allow));
    if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
      (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
    }
    continue;
  }
 }));
        (void)(((module->pending_cfg_skip) = 0));
      }
      if ((((r.tok).kind) ==19)) {
        int32_t ap_struct = (module->pending_allow_padding);
        int32_t ps_struct = (module->pending_soa_struct);
        int32_t pr_struct = (module->pending_repr_c_struct);
        int32_t pc_struct = (module->pending_repr_compatible_struct);
        int32_t pe_struct = (module->pending_export);
        (void)(((module->pending_allow_padding) = 0));
        (void)(((module->pending_soa_struct) = 0));
        (void)(((module->pending_repr_c_struct) = 0));
        (void)(((module->pending_repr_compatible_struct) = 0));
        (void)(((module->pending_export) = 0));
        int32_t allow_for_repr = ap_struct;
        if ((pr_struct !=0)) {
          (void)((allow_for_repr = 1));
        }
        int32_t nsl_before = (module->num_struct_layouts);
        if ((parser_parse_struct_record_layout_into(arena, module, lex, source, &(lex), allow_for_repr, ps_struct, pc_struct) !=0)) {
          /* wave679: P012 sticky → hard abort (no soft-skip false green). PLATFORM: SHARED */
          {
            extern int32_t parser_sig_type_hard_pending_c(void);
            if (parser_sig_type_hard_pending_c() != 0) {
              return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
            }
          }
          (void)(parser_skip_one_struct_into(&(lex), iter_start, source));
        } else {
          if (((pe_struct !=0) && ((module->num_struct_layouts) > nsl_before))) {
            (void)(pipeline_module_struct_layout_set_is_export(module, ((module->num_struct_layouts) - 1), 1));
          }
        }
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==47)) {
        int32_t pe_enum = (module->pending_export);
        (void)(((module->pending_export) = 0));
        int32_t nen_before = (module->num_module_enums);
        (void)(parser_skip_one_enum_register_into(module, &(lex), iter_start, source));
        if (((pe_enum !=0) && ((module->num_module_enums) > nen_before))) {
          (void)(pipeline_module_enum_set_is_export(module, ((module->num_module_enums) - 1), 1));
        }
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==54)) {
        (void)(parser_parse_one_extern_and_add_into(arena, module, iter_start, source, &(lex)));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)(parser_skip_one_extern_into(&(lex), lex, source));
        }
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==49)) {
        (void)(parser_skip_one_trait_into(&(lex), iter_start, source));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==50)) {
        (void)(parser_skip_one_impl_into(&(lex), iter_start, source));
        if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        } else {
          (void)((impl_body_depth = (impl_body_depth + 1)));
        }
        continue;
      }
      /* Impl closer after skip_one_impl parked at first method (wave390 UFCS).
       * PLATFORM: SHARED — must run before parse_strict unexpected-token. */
      if (((((r.tok).kind) ==85) && (impl_body_depth > 0))) {
        (void)((impl_body_depth = (impl_body_depth - 1)));
        continue;
      }
      if ((((r.tok).kind) !=1)) {
        struct parser_TrySkipAllowResult try_res = (struct parser_TrySkipAllowResult){ .lex = lex, .skipped = 0, ._pad = { 0 } };
        (void)(parser_parse_into_try_skip_allow_into(&(try_res), lex, r, source));
        if (((try_res.skipped) !=0)) {
          (void)(((module->pending_allow_padding) = 1));
          (void)(parser_lex_from_try_skip_into(&(lex), try_res));
          if ((((lex.pos) ==(iter_start.pos)) && ((lex.pos) < (source->length)))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==0)) {
          break;
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        continue;
      }
      if ((((r.tok).kind) ==0)) {
        if (((module->num_funcs) ==0)) {
          return parser_parse_into_result_empty_module_or_fail_tok(parser_diag_fail_at_token_kind(source));
        }
        /* wave424: trait completeness (parse_into slice). */
        return parser_parse_into_finish_ok(module, main_idx);
      }
      /* Latch export before body parse (G.7 ≡ struct pe_*); body must not clear pe. */
      int32_t pe_fn = (module->pending_export);
      (void)(((module->pending_export) = 0));
      struct lexer_Lexer lex_at_function = lexer_init();
      (void)((lex_at_function = current_tok_lex));
      (void)(parser_lex_from_next_into(&(lex), r));
      uint8_t parse_into_empty64[128] = {};
      struct parser_OneFuncResult res = parser_onefunc_scratch_empty();
      (void)((res = parser_onefunc_scratch_empty()));
      (void)(parser_onefunc_res_wire_dummy_head(&(res), lex, parse_into_empty64));
      (void)(parser_onefunc_res_wire_dummy_const_let(&(res)));
      (void)(parser_onefunc_res_wire_dummy_if_mul(&(res)));
      (void)(parser_onefunc_res_wire_dummy_call_binop(&(res), parse_into_empty64));
      (void)(parser_onefunc_res_wire_dummy_loop_call(&(res)));
      (void)(parser_onefunc_res_wire_dummy_for_if(&(res)));
      uint8_t empty64_lib_first[128] = {};
      struct parser_LibraryParseResult lib_first = (struct parser_LibraryParseResult){ .ok = 0, ._pad = { 0 }, .next_lex = lex_at_function, .name = {empty64_lib_first[0], empty64_lib_first[1], empty64_lib_first[2], empty64_lib_first[3], empty64_lib_first[4], empty64_lib_first[5], empty64_lib_first[6], empty64_lib_first[7], empty64_lib_first[8], empty64_lib_first[9], empty64_lib_first[10], empty64_lib_first[11], empty64_lib_first[12], empty64_lib_first[13], empty64_lib_first[14], empty64_lib_first[15], empty64_lib_first[16], empty64_lib_first[17], empty64_lib_first[18], empty64_lib_first[19], empty64_lib_first[20], empty64_lib_first[21], empty64_lib_first[22], empty64_lib_first[23], empty64_lib_first[24], empty64_lib_first[25], empty64_lib_first[26], empty64_lib_first[27], empty64_lib_first[28], empty64_lib_first[29], empty64_lib_first[30], empty64_lib_first[31], empty64_lib_first[32], empty64_lib_first[33], empty64_lib_first[34], empty64_lib_first[35], empty64_lib_first[36], empty64_lib_first[37], empty64_lib_first[38], empty64_lib_first[39], empty64_lib_first[40], empty64_lib_first[41], empty64_lib_first[42], empty64_lib_first[43], empty64_lib_first[44], empty64_lib_first[45], empty64_lib_first[46], empty64_lib_first[47], empty64_lib_first[48], empty64_lib_first[49], empty64_lib_first[50], empty64_lib_first[51], empty64_lib_first[52], empty64_lib_first[53], empty64_lib_first[54], empty64_lib_first[55], empty64_lib_first[56], empty64_lib_first[57], empty64_lib_first[58], empty64_lib_first[59], empty64_lib_first[60], empty64_lib_first[61], empty64_lib_first[62], empty64_lib_first[63]}, .name_len = 0, ._pad_tail = { 0 } };
      (void)((lib_first = (struct parser_LibraryParseResult){ .ok = 0, ._pad = { 0 }, .next_lex = lex_at_function, .name = {empty64_lib_first[0], empty64_lib_first[1], empty64_lib_first[2], empty64_lib_first[3], empty64_lib_first[4], empty64_lib_first[5], empty64_lib_first[6], empty64_lib_first[7], empty64_lib_first[8], empty64_lib_first[9], empty64_lib_first[10], empty64_lib_first[11], empty64_lib_first[12], empty64_lib_first[13], empty64_lib_first[14], empty64_lib_first[15], empty64_lib_first[16], empty64_lib_first[17], empty64_lib_first[18], empty64_lib_first[19], empty64_lib_first[20], empty64_lib_first[21], empty64_lib_first[22], empty64_lib_first[23], empty64_lib_first[24], empty64_lib_first[25], empty64_lib_first[26], empty64_lib_first[27], empty64_lib_first[28], empty64_lib_first[29], empty64_lib_first[30], empty64_lib_first[31], empty64_lib_first[32], empty64_lib_first[33], empty64_lib_first[34], empty64_lib_first[35], empty64_lib_first[36], empty64_lib_first[37], empty64_lib_first[38], empty64_lib_first[39], empty64_lib_first[40], empty64_lib_first[41], empty64_lib_first[42], empty64_lib_first[43], empty64_lib_first[44], empty64_lib_first[45], empty64_lib_first[46], empty64_lib_first[47], empty64_lib_first[48], empty64_lib_first[49], empty64_lib_first[50], empty64_lib_first[51], empty64_lib_first[52], empty64_lib_first[53], empty64_lib_first[54], empty64_lib_first[55], empty64_lib_first[56], empty64_lib_first[57], empty64_lib_first[58], empty64_lib_first[59], empty64_lib_first[60], empty64_lib_first[61], empty64_lib_first[62], empty64_lib_first[63]}, .name_len = 0, ._pad_tail = { 0 } }));
      (void)(parser_parse_one_function_library_into(&(lib_first), arena, module, lex_at_function, source));
      if ((lib_first.ok)) {
        (void)(parser_lex_from_library_into(&(lex), lib_first));
        if ((((lex.pos) ==(lex_at_function.pos)) && ((lex.pos) < (source->length)))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      (void)(parser_parse_one_function_impl(&(res), arena, lex, source));
      if (!((res.ok))) {
        return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
      }
      int32_t is_main_storage[1] = {};
      if (((((((res.name_len) ==4) && (((res.name))[0] ==109)) && (((res.name))[1] ==97)) && (((res.name))[2] ==105)) && (((res.name))[3] ==110))) {
        (void)(((is_main_storage)[0] = 1));
      }
      (void)(parser_diagnostic_parse_func_generic(((int32_t)((lex_at_function.pos))), (module->num_funcs), &(((res.name))[0]), (res.name_len), (res.num_generic_params), (is_main_storage)[0]));
      int32_t type_ref = 0;
      (void)((type_ref = (res.func_return_type_ref)));
      if ((type_ref ==0)) {
        (void)((type_ref = ast_ast_arena_type_alloc(arena)));
        if (((type_ref ==0) && ((module->num_funcs) ==0))) {
          (void)(ast_ast_arena_init(arena));
          (void)((type_ref = ast_ast_arena_type_alloc(arena)));
        }
        if ((type_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1001) };
        }
        struct ast_Type t_fb = ast_ast_arena_type_get(arena, type_ref);
        (void)(((t_fb.kind) = 0));
        (void)(((t_fb.name_len) = 0));
        (void)(((t_fb.elem_type_ref) = 0));
        (void)(((t_fb.array_size) = 0));
        (void)(ast_ast_arena_type_set(arena, type_ref, t_fb));
      }
      int32_t expr_ref = 0;
      (void)((expr_ref = ast_ast_arena_expr_alloc(arena)));
      if ((expr_ref ==0)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1002) };
      }
      struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
      (void)((e = ast_ast_arena_expr_get(arena, expr_ref)));
      if (((res.return_var_name_len) > 0)) {
        (void)(((e.kind) = 3));
        (void)(((e.var_name_len) = (res.return_var_name_len)));
        int32_t rvi = 0;
        while (((rvi < (res.return_var_name_len)) && (rvi < 128))) {
          (void)((((e.var_name))[rvi] = ((res.return_var_name))[rvi]));
          (void)((rvi = (rvi + 1)));
        }
        uint8_t rvz = ((uint8_t)(0));
        while ((rvi < 128)) {
          (void)((((e.var_name))[rvi] = rvz));
          (void)((rvi = (rvi + 1)));
        }
        (void)(((e.int_val) = 0));
        (void)(((e.resolved_type_ref) = 0));
      } else {
        (void)(((e.kind) = 0));
        (void)(((e.resolved_type_ref) = type_ref));
        (void)(((e.int_val) = (res.return_val)));
      }
      (void)(((e.line) = 0));
      (void)(((e.col) = 0));
      (void)(((e.binop_left_ref) = 0));
      (void)(((e.binop_right_ref) = 0));
      (void)(((e.unary_operand_ref) = 0));
      (void)(((e.if_cond_ref) = 0));
      (void)(((e.if_then_ref) = 0));
      (void)(((e.if_else_ref) = 0));
      (void)(((e.block_ref) = 0));
      (void)(((e.match_matched_ref) = 0));
      (void)(((e.match_num_arms) = 0));
      (void)(ast_expr_init_match_enum(&(e)));
      (void)(((e.field_access_base_ref) = 0));
      (void)(((e.field_access_field_len) = 0));
      (void)(((e.field_access_is_enum_variant) = 0));
      (void)(((e.field_access_offset) = 0));
      (void)(((e.index_base_ref) = 0));
      (void)(((e.index_index_ref) = 0));
      (void)(((e.index_base_is_slice) = 0));
      (void)(((e.call_callee_ref) = 0));
      (void)(((e.call_num_args) = 0));
      (void)(((e.method_call_base_ref) = 0));
      (void)(((e.method_call_name_len) = 0));
      (void)(((e.method_call_num_args) = 0));
      (void)(((e.const_folded_val) = 0));
      (void)(((e.const_folded_valid) = 0));
      (void)(((e.index_proven_in_bounds) = 0));
      (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
      int allow_legacy_tail_expr = 0;
      (void)((allow_legacy_tail_expr = ((((res.has_final_expr) || (res.has_explicit_return_kw)) || ((res.return_expr_ref) !=0)) || ((res.return_var_name_len) > 0))));
      int32_t final_expr_ref = 0;
      if (allow_legacy_tail_expr) {
        (void)((final_expr_ref = expr_ref));
      }
      if (((res.return_expr_ref) !=0)) {
        (void)((final_expr_ref = (res.return_expr_ref)));
      }
      if ((((res.return_var_name_len) > 0) && ((res.return_expr_ref) ==0))) {
        int32_t var_wrapped = parser_expr_wrap_in_return(arena, type_ref, final_expr_ref);
        if ((var_wrapped ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1003) };
        }
        (void)((final_expr_ref = var_wrapped));
      }
      if (((res.has_mul) && !((res.has_binop)))) {
        int32_t mul_right_ref = ast_ast_arena_expr_alloc(arena);
        if ((mul_right_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_right_ref);
        (void)(((mre.kind) = 0));
        (void)(((mre.resolved_type_ref) = type_ref));
        (void)(((mre.line) = 0));
        (void)(((mre.col) = 0));
        (void)(((mre.int_val) = (res.mul_right_val)));
        (void)(((mre.binop_left_ref) = 0));
        (void)(((mre.binop_right_ref) = 0));
        (void)(((mre.unary_operand_ref) = 0));
        (void)(((mre.if_cond_ref) = 0));
        (void)(((mre.if_then_ref) = 0));
        (void)(((mre.if_else_ref) = 0));
        (void)(((mre.block_ref) = 0));
        (void)(((mre.match_matched_ref) = 0));
        (void)(((mre.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(mre)));
        (void)(((mre.field_access_base_ref) = 0));
        (void)(((mre.field_access_field_len) = 0));
        (void)(((mre.field_access_is_enum_variant) = 0));
        (void)(((mre.field_access_offset) = 0));
        (void)(((mre.index_base_ref) = 0));
        (void)(((mre.index_index_ref) = 0));
        (void)(((mre.index_base_is_slice) = 0));
        (void)(((mre.call_callee_ref) = 0));
        (void)(((mre.call_num_args) = 0));
        (void)(((mre.method_call_base_ref) = 0));
        (void)(((mre.method_call_name_len) = 0));
        (void)(((mre.method_call_num_args) = 0));
        (void)(((mre.const_folded_val) = 0));
        (void)(((mre.const_folded_valid) = 0));
        (void)(((mre.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, mul_right_ref, mre));
        int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
        if ((mul_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
        (void)(((me.kind) = 6));
        (void)(((me.resolved_type_ref) = type_ref));
        (void)(((me.line) = 0));
        (void)(((me.col) = 0));
        (void)(((me.int_val) = 0));
        (void)(((me.binop_left_ref) = final_expr_ref));
        (void)(((me.binop_right_ref) = mul_right_ref));
        (void)(((me.unary_operand_ref) = 0));
        (void)(((me.if_cond_ref) = 0));
        (void)(((me.if_then_ref) = 0));
        (void)(((me.if_else_ref) = 0));
        (void)(((me.block_ref) = 0));
        (void)(((me.match_matched_ref) = 0));
        (void)(((me.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(me)));
        (void)(((me.field_access_base_ref) = 0));
        (void)(((me.field_access_field_len) = 0));
        (void)(((me.field_access_is_enum_variant) = 0));
        (void)(((me.field_access_offset) = 0));
        (void)(((me.index_base_ref) = 0));
        (void)(((me.index_index_ref) = 0));
        (void)(((me.index_base_is_slice) = 0));
        (void)(((me.call_callee_ref) = 0));
        (void)(((me.call_num_args) = 0));
        (void)(((me.method_call_base_ref) = 0));
        (void)(((me.method_call_name_len) = 0));
        (void)(((me.method_call_num_args) = 0));
        (void)(((me.const_folded_val) = 0));
        (void)(((me.const_folded_valid) = 0));
        (void)(((me.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, mul_ref, me));
        (void)((final_expr_ref = mul_ref));
      }
      if ((res.has_if_expr)) {
        int32_t cond_ref = 0;
        if (((res.if_cond_expr_ref) !=0)) {
          (void)((cond_ref = (res.if_cond_expr_ref)));
        } else {
          int32_t bool_type_ref = ast_ast_arena_type_alloc(arena);
          if ((bool_type_ref ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1005) };
          }
          struct ast_Type bt = ast_ast_arena_type_get(arena, bool_type_ref);
          (void)(((bt.kind) = 1));
          (void)(((bt.name_len) = 0));
          (void)(((bt.elem_type_ref) = 0));
          (void)(((bt.array_size) = 0));
          (void)(ast_ast_arena_type_set(arena, bool_type_ref, bt));
          (void)((cond_ref = ast_ast_arena_expr_alloc(arena)));
          if ((cond_ref ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          struct ast_Expr ce = ast_ast_arena_expr_get(arena, cond_ref);
          (void)(((ce.kind) = 2));
          (void)(((ce.resolved_type_ref) = bool_type_ref));
          (void)(((ce.line) = 0));
          (void)(((ce.col) = 0));
          if ((res.if_cond_true)) {
            (void)(((ce.int_val) = 1));
          } else {
            (void)(((ce.int_val) = 0));
          }
          (void)(((ce.binop_left_ref) = 0));
          (void)(((ce.binop_right_ref) = 0));
          (void)(((ce.unary_operand_ref) = 0));
          (void)(((ce.if_cond_ref) = 0));
          (void)(((ce.if_then_ref) = 0));
          (void)(((ce.if_else_ref) = 0));
          (void)(((ce.block_ref) = 0));
          (void)(((ce.match_matched_ref) = 0));
          (void)(((ce.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ce)));
          (void)(((ce.field_access_base_ref) = 0));
          (void)(((ce.field_access_field_len) = 0));
          (void)(((ce.field_access_is_enum_variant) = 0));
          (void)(((ce.field_access_offset) = 0));
          (void)(((ce.index_base_ref) = 0));
          (void)(((ce.index_index_ref) = 0));
          (void)(((ce.index_base_is_slice) = 0));
          (void)(((ce.call_callee_ref) = 0));
          (void)(((ce.call_num_args) = 0));
          (void)(((ce.method_call_base_ref) = 0));
          (void)(((ce.method_call_name_len) = 0));
          (void)(((ce.method_call_num_args) = 0));
          (void)(((ce.const_folded_val) = 0));
          (void)(((ce.const_folded_valid) = 0));
          (void)(((ce.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, cond_ref, ce));
        }
        int32_t then_ref = ast_ast_arena_expr_alloc(arena);
        if ((then_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr te = ast_ast_arena_expr_get(arena, then_ref);
        (void)(((te.kind) = 0));
        (void)(((te.resolved_type_ref) = type_ref));
        (void)(((te.line) = 0));
        (void)(((te.col) = 0));
        (void)(((te.int_val) = (res.if_then_val)));
        (void)(((te.binop_left_ref) = 0));
        (void)(((te.binop_right_ref) = 0));
        (void)(((te.unary_operand_ref) = 0));
        (void)(((te.if_cond_ref) = 0));
        (void)(((te.if_then_ref) = 0));
        (void)(((te.if_else_ref) = 0));
        (void)(((te.block_ref) = 0));
        (void)(((te.match_matched_ref) = 0));
        (void)(((te.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(te)));
        (void)(((te.field_access_base_ref) = 0));
        (void)(((te.field_access_field_len) = 0));
        (void)(((te.field_access_is_enum_variant) = 0));
        (void)(((te.field_access_offset) = 0));
        (void)(((te.index_base_ref) = 0));
        (void)(((te.index_index_ref) = 0));
        (void)(((te.index_base_is_slice) = 0));
        (void)(((te.call_callee_ref) = 0));
        (void)(((te.call_num_args) = 0));
        (void)(((te.method_call_base_ref) = 0));
        (void)(((te.method_call_name_len) = 0));
        (void)(((te.method_call_num_args) = 0));
        (void)(((te.const_folded_val) = 0));
        (void)(((te.const_folded_valid) = 0));
        (void)(((te.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, then_ref, te));
        int32_t else_ref = ast_ast_arena_expr_alloc(arena);
        if ((else_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr ee = ast_ast_arena_expr_get(arena, else_ref);
        (void)(((ee.kind) = 0));
        (void)(((ee.resolved_type_ref) = type_ref));
        (void)(((ee.line) = 0));
        (void)(((ee.col) = 0));
        (void)(((ee.int_val) = (res.if_else_val)));
        (void)(((ee.binop_left_ref) = 0));
        (void)(((ee.binop_right_ref) = 0));
        (void)(((ee.unary_operand_ref) = 0));
        (void)(((ee.if_cond_ref) = 0));
        (void)(((ee.if_then_ref) = 0));
        (void)(((ee.if_else_ref) = 0));
        (void)(((ee.block_ref) = 0));
        (void)(((ee.match_matched_ref) = 0));
        (void)(((ee.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(ee)));
        (void)(((ee.field_access_base_ref) = 0));
        (void)(((ee.field_access_field_len) = 0));
        (void)(((ee.field_access_is_enum_variant) = 0));
        (void)(((ee.field_access_offset) = 0));
        (void)(((ee.index_base_ref) = 0));
        (void)(((ee.index_index_ref) = 0));
        (void)(((ee.index_base_is_slice) = 0));
        (void)(((ee.call_callee_ref) = 0));
        (void)(((ee.call_num_args) = 0));
        (void)(((ee.method_call_base_ref) = 0));
        (void)(((ee.method_call_name_len) = 0));
        (void)(((ee.method_call_num_args) = 0));
        (void)(((ee.const_folded_val) = 0));
        (void)(((ee.const_folded_valid) = 0));
        (void)(((ee.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, else_ref, ee));
        int32_t if_expr_ref = ast_ast_arena_expr_alloc(arena);
        if ((if_expr_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr ie = ast_ast_arena_expr_get(arena, if_expr_ref);
        (void)(((ie.kind) = 25));
        (void)(((ie.resolved_type_ref) = type_ref));
        (void)(((ie.line) = 0));
        (void)(((ie.col) = 0));
        (void)(((ie.int_val) = 0));
        (void)(((ie.binop_left_ref) = 0));
        (void)(((ie.binop_right_ref) = 0));
        (void)(((ie.unary_operand_ref) = 0));
        (void)(((ie.if_cond_ref) = cond_ref));
        (void)(((ie.if_then_ref) = then_ref));
        (void)(((ie.if_else_ref) = else_ref));
        (void)(((ie.block_ref) = 0));
        (void)(((ie.match_matched_ref) = 0));
        (void)(((ie.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(ie)));
        (void)(((ie.field_access_base_ref) = 0));
        (void)(((ie.field_access_field_len) = 0));
        (void)(((ie.field_access_is_enum_variant) = 0));
        (void)(((ie.field_access_offset) = 0));
        (void)(((ie.index_base_ref) = 0));
        (void)(((ie.index_index_ref) = 0));
        (void)(((ie.index_base_is_slice) = 0));
        (void)(((ie.call_callee_ref) = 0));
        (void)(((ie.call_num_args) = 0));
        (void)(((ie.method_call_base_ref) = 0));
        (void)(((ie.method_call_name_len) = 0));
        (void)(((ie.method_call_num_args) = 0));
        (void)(((ie.const_folded_val) = 0));
        (void)(((ie.const_folded_valid) = 0));
        (void)(((ie.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, if_expr_ref, ie));
        (void)((final_expr_ref = if_expr_ref));
      }
      if (((res.return_expr_ref) ==0)) {
        if (((res.has_binop) || ((res.binop_right_val) !=0))) {
          uint8_t * res_pool = parser_onefunc_result_pool_ptr(&(res));
          int32_t left_ref = final_expr_ref;
          if ((((res.binop_left_param_idx) >=0) && ((res.binop_left_param_idx) < (res.num_params)))) {
            int32_t left_param_type_ref = pipeline_onefunc_param_type_ref(res_pool, (res.binop_left_param_idx));
            int32_t lpr = ast_ast_arena_expr_alloc(arena);
            if ((lpr !=0)) {
              struct ast_Expr lpe = ast_ast_arena_expr_get(arena, lpr);
              (void)(((lpe.kind) = 3));
              (void)(((lpe.resolved_type_ref) = left_param_type_ref));
              (void)(((lpe.line) = 0));
              (void)(((lpe.col) = 0));
              (void)(((lpe.var_name_len) = pipeline_onefunc_param_name_len(res_pool, (res.binop_left_param_idx))));
              int32_t lk = 0;
              while (((lk < (lpe.var_name_len)) && (lk < 64))) {
                (void)((((lpe.var_name))[lk] = pipeline_onefunc_param_name_byte_at(res_pool, (res.binop_left_param_idx), lk)));
                (void)((lk = (lk + 1)));
              }
              uint8_t lz = ((uint8_t)(0));
              while ((lk < 64)) {
                (void)((((lpe.var_name))[lk] = lz));
                (void)((lk = (lk + 1)));
              }
              (void)(driver_diagnostic_parser_onefunc_param_ref(&(((res.name))[0]), (res.name_len), &(((lpe.var_name))[0]), (lpe.var_name_len), 1, (res.binop_left_param_idx), left_param_type_ref));
              (void)(((lpe.binop_left_ref) = 0));
              (void)(((lpe.binop_right_ref) = 0));
              (void)(((lpe.unary_operand_ref) = 0));
              (void)(((lpe.if_cond_ref) = 0));
              (void)(((lpe.if_then_ref) = 0));
              (void)(((lpe.if_else_ref) = 0));
              (void)(((lpe.block_ref) = 0));
              (void)(((lpe.match_matched_ref) = 0));
              (void)(((lpe.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(lpe)));
              (void)(((lpe.field_access_base_ref) = 0));
              (void)(((lpe.field_access_field_len) = 0));
              (void)(((lpe.field_access_is_enum_variant) = 0));
              (void)(((lpe.field_access_offset) = 0));
              (void)(((lpe.index_base_ref) = 0));
              (void)(((lpe.index_index_ref) = 0));
              (void)(((lpe.index_base_is_slice) = 0));
              (void)(((lpe.call_callee_ref) = 0));
              (void)(((lpe.call_num_args) = 0));
              (void)(((lpe.method_call_base_ref) = 0));
              (void)(((lpe.method_call_name_len) = 0));
              (void)(((lpe.method_call_num_args) = 0));
              (void)(((lpe.const_folded_val) = 0));
              (void)(((lpe.const_folded_valid) = 0));
              (void)(((lpe.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, lpr, lpe));
              (void)((left_ref = lpr));
            }
          }
          int32_t right_ref = 0;
          if ((((res.binop_right_param_idx) >=0) && ((res.binop_right_param_idx) < (res.num_params)))) {
            int32_t right_param_type_ref = pipeline_onefunc_param_type_ref(res_pool, (res.binop_right_param_idx));
            int32_t rpr = ast_ast_arena_expr_alloc(arena);
            if ((rpr !=0)) {
              struct ast_Expr rpe = ast_ast_arena_expr_get(arena, rpr);
              (void)(((rpe.kind) = 3));
              (void)(((rpe.resolved_type_ref) = right_param_type_ref));
              (void)(((rpe.line) = 0));
              (void)(((rpe.col) = 0));
              (void)(((rpe.var_name_len) = pipeline_onefunc_param_name_len(res_pool, (res.binop_right_param_idx))));
              int32_t rk = 0;
              while (((rk < (rpe.var_name_len)) && (rk < 64))) {
                (void)((((rpe.var_name))[rk] = pipeline_onefunc_param_name_byte_at(res_pool, (res.binop_right_param_idx), rk)));
                (void)((rk = (rk + 1)));
              }
              uint8_t rz = ((uint8_t)(0));
              while ((rk < 64)) {
                (void)((((rpe.var_name))[rk] = rz));
                (void)((rk = (rk + 1)));
              }
              (void)(driver_diagnostic_parser_onefunc_param_ref(&(((res.name))[0]), (res.name_len), &(((rpe.var_name))[0]), (rpe.var_name_len), 2, (res.binop_right_param_idx), right_param_type_ref));
              (void)(((rpe.binop_left_ref) = 0));
              (void)(((rpe.binop_right_ref) = 0));
              (void)(((rpe.unary_operand_ref) = 0));
              (void)(((rpe.if_cond_ref) = 0));
              (void)(((rpe.if_then_ref) = 0));
              (void)(((rpe.if_else_ref) = 0));
              (void)(((rpe.block_ref) = 0));
              (void)(((rpe.match_matched_ref) = 0));
              (void)(((rpe.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(rpe)));
              (void)(((rpe.field_access_base_ref) = 0));
              (void)(((rpe.field_access_field_len) = 0));
              (void)(((rpe.field_access_is_enum_variant) = 0));
              (void)(((rpe.field_access_offset) = 0));
              (void)(((rpe.index_base_ref) = 0));
              (void)(((rpe.index_index_ref) = 0));
              (void)(((rpe.index_base_is_slice) = 0));
              (void)(((rpe.call_callee_ref) = 0));
              (void)(((rpe.call_num_args) = 0));
              (void)(((rpe.method_call_base_ref) = 0));
              (void)(((rpe.method_call_name_len) = 0));
              (void)(((rpe.method_call_num_args) = 0));
              (void)(((rpe.const_folded_val) = 0));
              (void)(((rpe.const_folded_valid) = 0));
              (void)(((rpe.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, rpr, rpe));
              (void)((right_ref = rpr));
            }
          } else {
            if ((res.has_mul)) {
              int32_t mul_left_ref = ast_ast_arena_expr_alloc(arena);
              if ((mul_left_ref ==0)) {
                return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
              }
              struct ast_Expr mle = ast_ast_arena_expr_get(arena, mul_left_ref);
              (void)(((mle.kind) = 0));
              (void)(((mle.resolved_type_ref) = type_ref));
              (void)(((mle.line) = 0));
              (void)(((mle.col) = 0));
              (void)(((mle.int_val) = (res.binop_right_val)));
              (void)(((mle.binop_left_ref) = 0));
              (void)(((mle.binop_right_ref) = 0));
              (void)(((mle.unary_operand_ref) = 0));
              (void)(((mle.if_cond_ref) = 0));
              (void)(((mle.if_then_ref) = 0));
              (void)(((mle.if_else_ref) = 0));
              (void)(((mle.block_ref) = 0));
              (void)(((mle.match_matched_ref) = 0));
              (void)(((mle.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(mle)));
              (void)(((mle.field_access_base_ref) = 0));
              (void)(((mle.field_access_field_len) = 0));
              (void)(((mle.field_access_is_enum_variant) = 0));
              (void)(((mle.field_access_offset) = 0));
              (void)(((mle.index_base_ref) = 0));
              (void)(((mle.index_index_ref) = 0));
              (void)(((mle.index_base_is_slice) = 0));
              (void)(((mle.call_callee_ref) = 0));
              (void)(((mle.call_num_args) = 0));
              (void)(((mle.method_call_base_ref) = 0));
              (void)(((mle.method_call_name_len) = 0));
              (void)(((mle.method_call_num_args) = 0));
              (void)(((mle.const_folded_val) = 0));
              (void)(((mle.const_folded_valid) = 0));
              (void)(((mle.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, mul_left_ref, mle));
              int32_t mul_r_ref = ast_ast_arena_expr_alloc(arena);
              if ((mul_r_ref ==0)) {
                return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
              }
              struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_r_ref);
              (void)(((mre.kind) = 0));
              (void)(((mre.resolved_type_ref) = type_ref));
              (void)(((mre.line) = 0));
              (void)(((mre.col) = 0));
              (void)(((mre.int_val) = (res.mul_right_val)));
              (void)(((mre.binop_left_ref) = 0));
              (void)(((mre.binop_right_ref) = 0));
              (void)(((mre.unary_operand_ref) = 0));
              (void)(((mre.if_cond_ref) = 0));
              (void)(((mre.if_then_ref) = 0));
              (void)(((mre.if_else_ref) = 0));
              (void)(((mre.block_ref) = 0));
              (void)(((mre.match_matched_ref) = 0));
              (void)(((mre.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(mre)));
              (void)(((mre.field_access_base_ref) = 0));
              (void)(((mre.field_access_field_len) = 0));
              (void)(((mre.field_access_is_enum_variant) = 0));
              (void)(((mre.field_access_offset) = 0));
              (void)(((mre.index_base_ref) = 0));
              (void)(((mre.index_index_ref) = 0));
              (void)(((mre.index_base_is_slice) = 0));
              (void)(((mre.call_callee_ref) = 0));
              (void)(((mre.call_num_args) = 0));
              (void)(((mre.method_call_base_ref) = 0));
              (void)(((mre.method_call_name_len) = 0));
              (void)(((mre.method_call_num_args) = 0));
              (void)(((mre.const_folded_val) = 0));
              (void)(((mre.const_folded_valid) = 0));
              (void)(((mre.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, mul_r_ref, mre));
              int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
              if ((mul_ref ==0)) {
                return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
              }
              struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
              (void)(((me.kind) = 6));
              (void)(((me.resolved_type_ref) = type_ref));
              (void)(((me.line) = 0));
              (void)(((me.col) = 0));
              (void)(((me.int_val) = 0));
              (void)(((me.binop_left_ref) = mul_left_ref));
              (void)(((me.binop_right_ref) = mul_r_ref));
              (void)(((me.unary_operand_ref) = 0));
              (void)(((me.if_cond_ref) = 0));
              (void)(((me.if_then_ref) = 0));
              (void)(((me.if_else_ref) = 0));
              (void)(((me.block_ref) = 0));
              (void)(((me.match_matched_ref) = 0));
              (void)(((me.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(me)));
              (void)(((me.field_access_base_ref) = 0));
              (void)(((me.field_access_field_len) = 0));
              (void)(((me.field_access_is_enum_variant) = 0));
              (void)(((me.field_access_offset) = 0));
              (void)(((me.index_base_ref) = 0));
              (void)(((me.index_index_ref) = 0));
              (void)(((me.index_base_is_slice) = 0));
              (void)(((me.call_callee_ref) = 0));
              (void)(((me.call_num_args) = 0));
              (void)(((me.method_call_base_ref) = 0));
              (void)(((me.method_call_name_len) = 0));
              (void)(((me.method_call_num_args) = 0));
              (void)(((me.const_folded_val) = 0));
              (void)(((me.const_folded_valid) = 0));
              (void)(((me.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, mul_ref, me));
              (void)((right_ref = mul_ref));
            } else {
              (void)((right_ref = ast_ast_arena_expr_alloc(arena)));
              if ((right_ref ==0)) {
                return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
              }
              struct ast_Expr re = ast_ast_arena_expr_get(arena, right_ref);
              (void)(((re.kind) = 0));
              (void)(((re.resolved_type_ref) = type_ref));
              (void)(((re.line) = 0));
              (void)(((re.col) = 0));
              (void)(((re.int_val) = (res.binop_right_val)));
              (void)(((re.binop_left_ref) = 0));
              (void)(((re.binop_right_ref) = 0));
              (void)(((re.unary_operand_ref) = 0));
              (void)(((re.if_cond_ref) = 0));
              (void)(((re.if_then_ref) = 0));
              (void)(((re.if_else_ref) = 0));
              (void)(((re.block_ref) = 0));
              (void)(((re.match_matched_ref) = 0));
              (void)(((re.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(re)));
              (void)(((re.field_access_base_ref) = 0));
              (void)(((re.field_access_field_len) = 0));
              (void)(((re.field_access_is_enum_variant) = 0));
              (void)(((re.field_access_offset) = 0));
              (void)(((re.index_base_ref) = 0));
              (void)(((re.index_index_ref) = 0));
              (void)(((re.index_base_is_slice) = 0));
              (void)(((re.call_callee_ref) = 0));
              (void)(((re.call_num_args) = 0));
              (void)(((re.method_call_base_ref) = 0));
              (void)(((re.method_call_name_len) = 0));
              (void)(((re.method_call_num_args) = 0));
              (void)(((re.const_folded_val) = 0));
              (void)(((re.const_folded_valid) = 0));
              (void)(((re.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, right_ref, re));
            }
          }
          int32_t add_ref = ast_ast_arena_expr_alloc(arena);
          if ((add_ref ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          struct ast_Expr ae = ast_ast_arena_expr_get(arena, add_ref);
          (void)(((ae.kind) = 4));
          (void)(((ae.resolved_type_ref) = type_ref));
          (void)(((ae.line) = 0));
          (void)(((ae.col) = 0));
          (void)(((ae.int_val) = 0));
          (void)(((ae.binop_left_ref) = left_ref));
          (void)(((ae.binop_right_ref) = right_ref));
          (void)(((ae.unary_operand_ref) = 0));
          (void)(((ae.if_cond_ref) = 0));
          (void)(((ae.if_then_ref) = 0));
          (void)(((ae.if_else_ref) = 0));
          (void)(((ae.block_ref) = 0));
          (void)(((ae.match_matched_ref) = 0));
          (void)(((ae.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ae)));
          (void)(((ae.field_access_base_ref) = 0));
          (void)(((ae.field_access_field_len) = 0));
          (void)(((ae.field_access_is_enum_variant) = 0));
          (void)(((ae.field_access_offset) = 0));
          (void)(((ae.index_base_ref) = 0));
          (void)(((ae.index_index_ref) = 0));
          (void)(((ae.index_base_is_slice) = 0));
          (void)(((ae.call_callee_ref) = 0));
          (void)(((ae.call_num_args) = 0));
          (void)(((ae.method_call_base_ref) = 0));
          (void)(((ae.method_call_name_len) = 0));
          (void)(((ae.method_call_num_args) = 0));
          (void)(((ae.const_folded_val) = 0));
          (void)(((ae.const_folded_valid) = 0));
          (void)(((ae.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, add_ref, ae));
          (void)((final_expr_ref = add_ref));
        }
      }
      if ((res.has_unary_neg)) {
        int32_t operand_ref = ast_ast_arena_expr_alloc(arena);
        if ((operand_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr oe = ast_ast_arena_expr_get(arena, operand_ref);
        (void)(((oe.kind) = 0));
        (void)(((oe.resolved_type_ref) = type_ref));
        (void)(((oe.line) = 0));
        (void)(((oe.col) = 0));
        (void)(((oe.int_val) = (res.return_val)));
        (void)(((oe.binop_left_ref) = 0));
        (void)(((oe.binop_right_ref) = 0));
        (void)(((oe.unary_operand_ref) = 0));
        (void)(((oe.if_cond_ref) = 0));
        (void)(((oe.if_then_ref) = 0));
        (void)(((oe.if_else_ref) = 0));
        (void)(((oe.block_ref) = 0));
        (void)(((oe.match_matched_ref) = 0));
        (void)(((oe.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(oe)));
        (void)(((oe.field_access_base_ref) = 0));
        (void)(((oe.field_access_field_len) = 0));
        (void)(((oe.field_access_is_enum_variant) = 0));
        (void)(((oe.field_access_offset) = 0));
        (void)(((oe.index_base_ref) = 0));
        (void)(((oe.index_index_ref) = 0));
        (void)(((oe.index_base_is_slice) = 0));
        (void)(((oe.call_callee_ref) = 0));
        (void)(((oe.call_num_args) = 0));
        (void)(((oe.method_call_base_ref) = 0));
        (void)(((oe.method_call_name_len) = 0));
        (void)(((oe.method_call_num_args) = 0));
        (void)(((oe.const_folded_val) = 0));
        (void)(((oe.const_folded_valid) = 0));
        (void)(((oe.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, operand_ref, oe));
        int32_t neg_ref = ast_ast_arena_expr_alloc(arena);
        if ((neg_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr ne = ast_ast_arena_expr_get(arena, neg_ref);
        (void)(((ne.kind) = 22));
        (void)(((ne.resolved_type_ref) = type_ref));
        (void)(((ne.line) = 0));
        (void)(((ne.col) = 0));
        (void)(((ne.int_val) = 0));
        (void)(((ne.binop_left_ref) = 0));
        (void)(((ne.binop_right_ref) = 0));
        (void)(((ne.unary_operand_ref) = operand_ref));
        (void)(((ne.if_cond_ref) = 0));
        (void)(((ne.if_then_ref) = 0));
        (void)(((ne.if_else_ref) = 0));
        (void)(((ne.block_ref) = 0));
        (void)(((ne.match_matched_ref) = 0));
        (void)(((ne.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(ne)));
        (void)(((ne.field_access_base_ref) = 0));
        (void)(((ne.field_access_field_len) = 0));
        (void)(((ne.field_access_is_enum_variant) = 0));
        (void)(((ne.field_access_offset) = 0));
        (void)(((ne.index_base_ref) = 0));
        (void)(((ne.index_index_ref) = 0));
        (void)(((ne.index_base_is_slice) = 0));
        (void)(((ne.call_callee_ref) = 0));
        (void)(((ne.call_num_args) = 0));
        (void)(((ne.method_call_base_ref) = 0));
        (void)(((ne.method_call_name_len) = 0));
        (void)(((ne.method_call_num_args) = 0));
        (void)(((ne.const_folded_val) = 0));
        (void)(((ne.const_folded_valid) = 0));
        (void)(((ne.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, neg_ref, ne));
        (void)((final_expr_ref = neg_ref));
      }
      if (((((res.has_call_expr) && ((res.return_expr_ref) ==0)) && ((res.call_callee_len) > 0)) && ((res.call_callee_len) <=127))) {
        uint8_t * call_pool = parser_onefunc_result_pool_ptr(&(res));
        int32_t callee_ref = ast_ast_arena_expr_alloc(arena);
        if ((callee_ref !=0)) {
          struct ast_Expr ve = ast_ast_arena_expr_get(arena, callee_ref);
          (void)(((ve.kind) = 3));
          (void)(((ve.resolved_type_ref) = 0));
          (void)(((ve.line) = 0));
          (void)(((ve.col) = 0));
          (void)(((ve.var_name_len) = (res.call_callee_len)));
          int32_t ck = 0;
          while (((ck < (res.call_callee_len)) && (ck < 128))) {
            (void)((((ve.var_name))[ck] = ((res.call_callee_name))[ck]));
            (void)((ck = (ck + 1)));
          }
          uint8_t z = ((uint8_t)(0));
          while ((ck < 128)) {
            (void)((((ve.var_name))[ck] = z));
            (void)((ck = (ck + 1)));
          }
          (void)(((ve.binop_left_ref) = 0));
          (void)(((ve.binop_right_ref) = 0));
          (void)(((ve.unary_operand_ref) = 0));
          (void)(((ve.if_cond_ref) = 0));
          (void)(((ve.if_then_ref) = 0));
          (void)(((ve.if_else_ref) = 0));
          (void)(((ve.block_ref) = 0));
          (void)(((ve.match_matched_ref) = 0));
          (void)(((ve.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ve)));
          (void)(((ve.field_access_base_ref) = 0));
          (void)(((ve.field_access_field_len) = 0));
          (void)(((ve.field_access_is_enum_variant) = 0));
          (void)(((ve.field_access_offset) = 0));
          (void)(((ve.index_base_ref) = 0));
          (void)(((ve.index_index_ref) = 0));
          (void)(((ve.index_base_is_slice) = 0));
          (void)(((ve.call_callee_ref) = 0));
          (void)(((ve.call_num_args) = 0));
          (void)(((ve.method_call_base_ref) = 0));
          (void)(((ve.method_call_name_len) = 0));
          (void)(((ve.method_call_num_args) = 0));
          (void)(((ve.const_folded_val) = 0));
          (void)(((ve.const_folded_valid) = 0));
          (void)(((ve.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, callee_ref, ve));
          int32_t call_ref = ast_ast_arena_expr_alloc(arena);
          if ((call_ref !=0)) {
            struct ast_Expr ce = ast_ast_arena_expr_get(arena, call_ref);
            (void)(parser_expr_set_common_zeros(&(ce)));
            (void)(((ce.kind) = 48));
            (void)(((ce.resolved_type_ref) = type_ref));
            (void)(((ce.line) = 0));
            (void)(((ce.col) = 0));
            (void)(((ce.call_callee_ref) = callee_ref));
            if (((res.call_num_args) > 0)) {
              (void)(((ce.call_num_args) = (res.call_num_args)));
            } else {
              (void)(((ce.call_num_args) = (res.num_params)));
            }
            (void)(ast_ast_arena_expr_set(arena, call_ref, ce));
            int32_t arg_i = 0;
            while ((arg_i < (ce.call_num_args))) {
              int32_t arg_ref = ast_ast_arena_expr_alloc(arena);
              if ((arg_ref !=0)) {
                struct ast_Expr ae = ast_ast_arena_expr_get(arena, arg_ref);
                (void)(((ae.resolved_type_ref) = 0));
                (void)(((ae.line) = 0));
                (void)(((ae.col) = 0));
                if ((((res.call_num_args) > 0) && (arg_i < (res.call_num_args)))) {
                  (void)(((ae.kind) = 0));
                  (void)(((ae.int_val) = pipeline_onefunc_call_arg_val_at(call_pool, arg_i)));
                } else {
                  (void)(((ae.kind) = 3));
                  (void)(((ae.var_name_len) = pipeline_onefunc_param_name_len(call_pool, arg_i)));
                  int32_t k = 0;
                  while (((k < (ae.var_name_len)) && (k < 128))) {
                    (void)((((ae.var_name))[k] = pipeline_onefunc_param_name_byte_at(call_pool, arg_i, k)));
                    (void)((k = (k + 1)));
                  }
                  uint8_t z = ((uint8_t)(0));
                  while ((k < 64)) {
                    (void)((((ae.var_name))[k] = z));
                    (void)((k = (k + 1)));
                  }
                }
                (void)(parser_expr_set_common_zeros(&(ae)));
                (void)(ast_ast_arena_expr_set(arena, arg_ref, ae));
                (void)(pipeline_expr_append_call_arg(arena, call_ref, arg_ref));
              }
              (void)((arg_i = (arg_i + 1)));
            }
            (void)((final_expr_ref = call_ref));
          }
        }
      }
      int32_t block_ref = 0;
      (void)((block_ref = ast_ast_arena_block_alloc(arena)));
      if ((block_ref ==0)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1010) };
      }
      struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(((b.num_consts) = 0));
      (void)(((b.num_lets) = 0));
      (void)(((b.num_early_lets) = 0));
      (void)(((b.num_loops) = 0));
      (void)(((b.num_for_loops) = 0));
      (void)(((b.num_if_stmts) = 0));
      (void)(((b.num_regions) = 0));
      (void)(((b.num_defers) = 0));
      (void)(((b.num_labeled_stmts) = 0));
      (void)(((b.num_expr_stmts) = 0));
      (void)(((b.final_expr_ref) = 0));
      (void)(((b.num_stmt_order) = 0));
      (void)(((b.parent_block_ref) = 0));
      (void)(ast_ast_arena_block_set(arena, block_ref, b));
      if (parser_should_wrap_func_tail_in_return(arena, &(res), type_ref)) {
        int32_t wrapped_fe = parser_expr_wrap_in_return(arena, type_ref, final_expr_ref);
        if ((wrapped_fe ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1011) };
        }
        (void)((final_expr_ref = wrapped_fe));
      }
      (void)(parser_diagnostic_parse_commit_pre(arena, &(((res.name))[0]), (res.name_len), block_ref, parser_onefunc_result_pool_ptr(&(res)), final_expr_ref));
      if (!(parser_fill_block_const_let_from_res(arena, block_ref, &(res), type_ref))) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      int32_t n_while_pool = 0;
      (void)((n_while_pool = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_loops) = n_while_pool));
      (void)(pipeline_block_fill_whiles_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_while_pool));
      int32_t n_for_pool = 0;
      (void)((n_for_pool = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_for_loops) = n_for_pool));
      (void)(pipeline_block_fill_fors_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_for_pool));
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      int32_t n_if_pool = 0;
      (void)((n_if_pool = pipeline_onefunc_num_if_stmts(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_if_stmts) = n_if_pool));
      (void)(pipeline_block_fill_ifs_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_if_pool));
      int32_t n_reg_pool = 0;
      (void)((n_reg_pool = pipeline_onefunc_num_regions(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(pipeline_block_fill_regions_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_reg_pool));
      int32_t n_def_pool = 0;
      (void)((n_def_pool = pipeline_onefunc_num_defers(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(pipeline_block_fill_defers_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_def_pool));
      /* wave379: labeled/goto before stmt_order kind=7 */
      {
        int32_t n_lab_pool = 0;
        (void)((n_lab_pool = pipeline_onefunc_num_labeleds(parser_onefunc_result_pool_ptr(&(res)))));
        (void)(pipeline_block_fill_labeled_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_lab_pool));
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      if (((res.num_src_stmt_order) > 0)) {
        (void)(pipeline_block_fill_expr_stmts_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(&(res)))));
        (void)(pipeline_block_fill_stmt_order_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), pipeline_onefunc_num_src_stmt_order(parser_onefunc_result_pool_ptr(&(res)))));
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      } else {
        int32_t ci2 = 0;
        while ((ci2 < (b.num_consts))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 0, ci2) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((ci2 = (ci2 + 1)));
        }
        int32_t li2 = 0;
        while ((li2 < (b.num_lets))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 1, li2) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((li2 = (li2 + 1)));
        }
        int32_t loop_i = 0;
        while ((loop_i < (b.num_loops))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 3, loop_i) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((loop_i = (loop_i + 1)));
        }
        int32_t for_i = 0;
        while ((for_i < (b.num_for_loops))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 4, for_i) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((for_i = (for_i + 1)));
        }
        int32_t if_oi = 0;
        while ((if_oi < (b.num_if_stmts))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 5, if_oi) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((if_oi = (if_oi + 1)));
        }
        int32_t reg_oi = 0;
        while ((reg_oi < pipeline_onefunc_num_regions(parser_onefunc_result_pool_ptr(&(res))))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 6, reg_oi) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((reg_oi = (reg_oi + 1)));
        }
        if ((!(ast_ref_is_null(final_expr_ref)) && ((b.num_expr_stmts) ==0))) {
          int32_t fin_ex = pipeline_block_append_expr_stmt(arena, block_ref, final_expr_ref);
          if ((fin_ex < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)(((b.final_expr_ref) = 0));
          (void)((final_expr_ref = 0));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 2, fin_ex) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        }
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(((b.final_expr_ref) = final_expr_ref));
      if ((((b.num_expr_stmts) > 0) && !(ast_ref_is_null(final_expr_ref)))) {
        struct ast_Expr fe_dedup = ast_ast_arena_expr_get(arena, final_expr_ref);
        if (((fe_dedup.kind) !=41)) {
          (void)(((b.final_expr_ref) = 0));
        }
      }
      (void)(ast_ast_arena_block_set(arena, block_ref, b));
      (void)(pipeline_block_with_arena_fixup_stmt_order(arena, block_ref));
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(parser_diagnostic_parse_commit_post(arena, &(((res.name))[0]), (res.name_len), block_ref, parser_onefunc_result_pool_ptr(&(res))));
      int32_t fi = -(1);
      (void)((fi = pipeline_module_func_alloc_slot(module)));
      if ((fi < 0)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1000) };
      }
      (void)(pipeline_module_func_name_write(module, fi, &(((res.name))[0]), (res.name_len)));
      (void)(pipeline_module_func_set_num_params(module, fi, (res.num_params)));
      (void)(pipeline_module_func_set_num_generic_params(module, fi, (res.num_generic_params)));
      /* Cap 10.7.1: OneFuncResult.is_variadic → module Func (≡ parser.x). */
      (void)(pipeline_module_func_set_is_variadic(module, fi, (res.is_variadic)));
      uint8_t * mod_pool = parser_onefunc_result_pool_ptr(&(res));
      int32_t p = 0;
      while ((p < (res.num_params))) {
        uint8_t pname32[128] = {};
        (void)(pipeline_onefunc_param_name_copy32(mod_pool, p, &((pname32)[0])));
        (void)(pipeline_module_func_param_write(module, fi, p, &((pname32)[0]), pipeline_onefunc_param_name_len(mod_pool, p), pipeline_onefunc_param_type_ref(mod_pool, p)));
        (void)((p = (p + 1)));
      }
      (void)(pipeline_module_func_set_return_type(module, fi, type_ref));
      (void)(pipeline_module_func_set_body_ref(module, fi, block_ref));
      (void)(pipeline_module_func_set_is_extern(module, fi, 0));
      (void)(pipeline_module_func_set_is_async(module, fi, (func_is_async_storage)[0]));
      (void)(pipeline_module_func_set_is_export(module, fi, pe_fn));
      (void)(pipeline_module_func_set_is_used(module, fi, (module->pending_used)));
      (void)(((module->pending_used) = 0));
      (void)(pipeline_module_func_set_is_naked(module, fi, (module->pending_naked)));
      (void)(((module->pending_naked) = 0));
      (void)(pipeline_module_func_set_is_entry(module, fi, (module->pending_entry)));
      (void)(((module->pending_entry) = 0));
      (void)(pipeline_module_func_set_is_no_mangle(module, fi, (module->pending_no_mangle)));
      (void)(((module->pending_no_mangle) = 0));
      (void)(pipeline_module_func_set_is_interrupt(module, fi, (module->pending_interrupt)));
      (void)(((module->pending_interrupt) = 0));
      if (((is_main_storage)[0] !=0)) {
        (void)((main_idx = fi));
      }
      (void)(parser_lex_from_onefunc_next_into(&(lex), &(res)));
      (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
    }
    if (((module->num_funcs) ==0)) {
      return parser_parse_into_result_empty_module_or_fail_tok(parser_diag_fail_at_token_kind(source));
    }
    /* wave424: trait completeness (parse_into slice). */
    return parser_parse_into_finish_ok(module, main_idx);
  }
}
extern void parser_parse_one_top_level_let_into_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, int is_const, struct parser_TopLevelLetResult * out);
void parser_parse_one_top_level_let_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, int is_const, struct parser_TopLevelLetResult * out) {
  (void)(parser_parse_one_top_level_let_into_glue(arena, module, lex, source, is_const, out));
}
extern void parser_parse_one_type_alias_into_glue(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_TypeAliasResult * out);
void parser_parse_one_type_alias_into(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, struct xlang_slice_uint8_t * source, struct parser_TypeAliasResult * out) {
  (void)(parser_parse_one_type_alias_into_glue(arena, module, lex, source, out));
}
void parser_parse_primary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_primary_into(arena, lex, &(slice), out));
  }
}
void parser_parse_unary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_unary_into(arena, lex, &(slice), out));
  }
}
void parser_parse_cast_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_cast_into(arena, lex, &(slice), out));
  }
}
void parser_parse_term_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_term_into(arena, lex, &(slice), out));
  }
}
void parser_parse_addsub_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_addsub_into(arena, lex, &(slice), out));
  }
}
void parser_parse_shift_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_shift_into(arena, lex, &(slice), out));
  }
}
void parser_parse_relcompare_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_relcompare_into(arena, lex, &(slice), out));
  }
}
void parser_parse_compare_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_compare_into(arena, lex, &(slice), out));
  }
}
void parser_parse_bitand_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_bitand_into(arena, lex, &(slice), out));
  }
}
void parser_parse_bitxor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_bitxor_into(arena, lex, &(slice), out));
  }
}
void parser_parse_bitor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_bitor_into(arena, lex, &(slice), out));
  }
}
void parser_parse_logand_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_logand_into(arena, lex, &(slice), out));
  }
}
void parser_parse_logor_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_logor_into(arena, lex, &(slice), out));
  }
}
void parser_parse_ternary_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_ternary_into(arena, lex, &(slice), out));
  }
}
void parser_parse_assign_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_assign_into(arena, lex, &(slice), out));
  }
}
void parser_parse_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_expr_into(arena, lex, &(slice), out));
  }
}
void parser_finish_struct_lit_from_type_ident_into_buf(struct ast_ASTArena * arena, int32_t lit_ref, struct lexer_Lexer lex_in_brace, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_finish_struct_lit_from_type_ident_into(arena, lit_ref, lex_in_brace, &(slice), out));
  }
}
void parser_parse_cond_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_start, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_cond_expr_into(arena, lex_start, &(slice), out));
  }
}
int parser_parse_if_stmt_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, uint8_t * data, int32_t len, int32_t type_ref, int32_t * out_cond, int32_t * out_then, int32_t * out_else, struct lexer_Lexer * lex_out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_if_stmt_into(arena, lex_at_if, &(slice), type_ref, out_cond, out_then, out_else, lex_out);
  }
  return 0;
}
void parser_parse_block_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_after_lbrace, uint8_t * data, int32_t len, int32_t type_ref, struct parser_ParseBlockResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_block_into(arena, lex_after_lbrace, &(slice), type_ref, out));
  }
}
void parser_parse_if_expr_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex_at_if, uint8_t * data, int32_t len, int32_t type_ref, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_if_expr_into(arena, lex_at_if, &(slice), type_ref, out));
  }
}
void parser_parse_match_subject_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_match_subject_into(arena, lex, &(slice), out));
  }
}
void parser_parse_match_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_match_into(arena, lex, &(slice), out));
  }
}
void parser_parse_at_simd_builtin_into_buf(struct ast_ASTArena * arena, struct lexer_LexerResult r0, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_at_simd_builtin_into(arena, r0, &(slice), out));
  }
}
void parser_parse_as_suffix_into_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct parser_ParseExprResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_as_suffix_into(arena, &(slice), out));
  }
}
int32_t parser_parse_type_ref_for_arena_into_buf(struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * out_lex) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_type_ref_for_arena_into(arena, lex, &(slice), out_lex);
  }
  return 0;
}
int32_t parser_parse_body_let_bracket_compound_init_ref_buf(struct ast_ASTArena * arena, size_t bracket_start, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out, struct lexer_LexerResult * r_out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_body_let_bracket_compound_init_ref(arena, bracket_start, lex, &(slice), lex_out, r_out);
  }
  return 0;
}
int32_t parser_parse_struct_record_layout_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * out_lex, int32_t allow_pad, int32_t force_soa, int32_t repr_compat) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_struct_record_layout_into(arena, module, lex, &(slice), out_lex, allow_pad, force_soa, repr_compat);
  }
  return 0;
}
int parser_parse_one_function_library_scan_buf(struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_LibraryParseScanResult * result) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_parse_one_function_library_scan(lex, &(slice), result);
  }
  return 0;
}
int32_t parser_alloc_pointee_type_ref_from_tok_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct lexer_LexerResult * r) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_alloc_pointee_type_ref_from_tok(arena, &(slice), r);
  }
  return 0;
}
int32_t parser_vector_type_ref_from_ident_spelling_buf(struct ast_ASTArena * arena, uint8_t * data, int32_t len, struct lexer_LexerResult r) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    return parser_vector_type_ref_from_ident_spelling(arena, &(slice), r);
  }
  return 0;
}
void parser_parse_one_top_level_let_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, int is_const, struct parser_TopLevelLetResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_one_top_level_let_into(arena, module, lex, &(slice), is_const, out));
  }
}
void parser_parse_one_type_alias_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct parser_TypeAliasResult * out) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_parse_one_type_alias_into(arena, module, lex, &(slice), out));
  }
}
void parser_skip_balanced_parens_slice_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_balanced_parens_into(out, lex, &(slice)));
  }
}
void parser_skip_balanced_braces_slice_into_buf(struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_skip_balanced_braces_into(out, lex, &(slice)));
  }
}
void parser_module_append_enum_variants_and_skip_body_slice_into_buf(struct ast_Module * module, int32_t enum_idx, struct lexer_Lexer * out, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  {
    struct xlang_slice_uint8_t slice = parser_slice_from_buf(data, len);
    (void)(parser_module_append_enum_variants_and_skip_body_into(module, enum_idx, out, lex, &(slice)));
  }
}
void parser_parse_one_extern_skip_buf(struct parser_ExternParseResult * out, struct ast_ASTArena * arena, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  (void)(parser_parse_one_extern_skip_into_buf(out, arena, lex, data, len));
}
void parser_parse_one_extern_and_add_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len, struct lexer_Lexer * lex_out) {
  (void)(parser_parse_one_extern_and_add_into_buf(arena, module, lex, data, len, lex_out));
}
struct parser_LibraryParseResult parser_parse_one_function_library_from_buf(struct ast_ASTArena * arena, struct ast_Module * module, struct lexer_Lexer lex, uint8_t * data, int32_t len) {
  return parser_parse_one_function_library_buf(arena, module, lex, data, len);
}
struct parser_TrySkipAllowResult parser_parse_into_try_skip_allow_from_buf(struct lexer_Lexer lex, struct lexer_LexerResult r, uint8_t * data, int32_t len) {
  return parser_parse_into_try_skip_allow_buf(lex, r, data, len);
}
struct parser_ParseIntoResult parser_parse_into_buf(struct ast_ASTArena * arena, struct ast_Module * module, uint8_t * data, int32_t len) {
  {
    /* wave269: clear L001 sticky before scanning this source buffer. */
    lexer_unclosed_block_comment_reset();
    lexer_unclosed_string_reset();
    lexer_illegal_char_reset();
    lexer_incomplete_hex_reset();
    lexer_incomplete_exp_reset();
    lexer_incomplete_bin_reset();
    lexer_incomplete_oct_reset();
    lexer_invalid_digit_sep_reset();
    lexer_invalid_type_suffix_reset();
    lexer_invalid_escape_reset();
  lexer_string_lit_overflow_reset();
  lexer_ident_too_long_reset();
    /* wave676: clear sticky P011 so a prior file cannot poison this parse. */
    {
      extern void parser_sig_type_hard_reset_c(void);
      parser_sig_type_hard_reset_c();
    }
    /* wave421/wave425: trait registry + stash arena for return type kind checks. */
    {
      extern void xlang_trait_reg_reset_c(void *arena);
      xlang_trait_reg_reset_c((void *)arena);
    }
    /*
     * wave439-rootcause: refresh the generic-bound source stash for THIS file.
     * xlang_generic_bound_stash_source_buf_c stashes a bare pointer into the
     * current parse buffer for later tokenization by xlang_generic_bound_scan_c
     * (invoked from xlang_trait_check_impls_complete_c). The previous design only
     * stashed lazily inside skip_one_struct/enum/trait_into_slice_c, so a file
     * with no top-level struct/enum/trait never refreshed the stash — the global
     * then pointed at a PREVIOUS file's freed buffer (use-after-free → 92 L003
     * false errors in directory check mode). Stashing at every parse_into_buf
     * entry guarantees the stash always reflects the live buffer of the file
     * currently being parsed, eliminating cross-file dangling. PLATFORM: SHARED.
     */
    {
      extern void xlang_generic_bound_stash_source_buf_c(uint8_t *data, int32_t len);
      xlang_generic_bound_stash_source_buf_c(data, len);
    }
    struct lexer_Lexer lex = lexer_init();
    int32_t main_idx = -(1);
    /* skip_one_impl leaves the lexer inside `{...}`; nest counts those bodies
     * so the matching `}` is an impl closer, not unexpected junk. */
    int32_t impl_body_depth_buf = 0;
    struct parser_CollectImportsResult import_res = (struct parser_CollectImportsResult){ .lex = lex };
    (void)(parser_collect_imports_buf(lex, data, len, module, &(import_res)));
    (void)(parser_copy_lex_from_import_into(&(lex), import_res));
    int32_t loop_count_buf = 0;
    while ((1 ==1)) {
      if ((loop_count_buf >=131072)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1003) };
      }
      (void)((loop_count_buf = (loop_count_buf + 1)));
      struct lexer_Lexer iter_start_buf = lex;
      struct lexer_LexerResult r = (struct lexer_LexerResult){ .next_lex = lex, .tok = (struct token_Token){ .kind = 0, .line = 0, .col = 0, .int_val = 0, .float_val = 0.0, .ident = 0, .ident_len = 0 }, .token_start = 0 };
      struct lexer_Lexer current_tok_lex_buf = lex;
      (void)(lexer_next_buf_into(&(r), lex, data, len));
      (void)(parser_lex_from_next_into(&(lex), r));
      int32_t func_is_async_buf[1] = {};
      (void)(((func_is_async_buf)[0] = 0));
      if ((((r.tok).kind) ==55)) {
        (void)(((func_is_async_buf)[0] = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        (void)((current_tok_lex_buf = lex));
        (void)(lexer_next_buf_into(&(r), lex, data, len));
        (void)(parser_lex_from_next_into(&(lex), r));
      }
      if ((((r.tok).kind) ==23)) {
        (void)(((module->pending_soa_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==24)) {
        if ((((r.tok).int_val) ==0)) {
          (void)(((module->pending_cfg_skip) = 1));
        }
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==25)) {
        (void)(((module->pending_repr_c_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==26)) {
        (void)(((module->pending_repr_compatible_struct) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==27)) {
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==31)) {
        (void)(((module->pending_used) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==29)) {
        (void)(((module->pending_naked) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==30)) {
        (void)(((module->pending_entry) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==32)) {
        (void)(((module->pending_no_mangle) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==35)) {
        (void)(((module->pending_interrupt) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==131)) {
        (void)(((module->pending_export) = 1));
        (void)(parser_lex_from_next_into(&(lex), r));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if (((module->pending_cfg_skip) !=0)) {
        if ((((r.tok).kind) ==19)) {
          (void)(parser_skip_one_struct_into_buf(&(lex), iter_start_buf, data, len));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==3)) {
          (void)(parser_skip_one_top_level_const_into_buf(&(lex), iter_start_buf, data, len));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==2)) {
          (void)(parser_skip_one_top_level_let_into_buf(&(lex), iter_start_buf, data, len));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((((r.tok).kind) ==1) || ((func_is_async_buf)[0] !=0)) || (((r.tok).kind) ==54))) {
          (void)(parser_skip_one_function_full_into_buf(&(lex), iter_start_buf, data, len));
          (void)(((module->pending_cfg_skip) = 0));
          (void)(((module->pending_export) = 0));
          (void)(((func_is_async_buf)[0] = 0));
          if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        (void)(({   struct parser_TrySkipAllowResult try_cfg_allow_buf = (struct parser_TrySkipAllowResult){ .lex = lex, .skipped = 0, ._pad = { 0 } };
  (void)(parser_parse_into_try_skip_allow_into_buf(&(try_cfg_allow_buf), lex, r, data, len));
  if (((try_cfg_allow_buf.skipped) !=0)) {
    (void)(parser_lex_from_try_skip_into(&(lex), try_cfg_allow_buf));
    if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
      (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
    }
    continue;
  }
 }));
        (void)(((module->pending_cfg_skip) = 0));
      }
      if ((((r.tok).kind) ==19)) {
        struct lexer_Lexer lex_kw = iter_start_buf;
        int32_t ap_sb = (module->pending_allow_padding);
        int32_t ps_sb = (module->pending_soa_struct);
        int32_t pr_sb = (module->pending_repr_c_struct);
        int32_t pc_sb = (module->pending_repr_compatible_struct);
        int32_t pe_sb = (module->pending_export);
        (void)(((module->pending_allow_padding) = 0));
        (void)(((module->pending_soa_struct) = 0));
        (void)(((module->pending_repr_c_struct) = 0));
        (void)(((module->pending_repr_compatible_struct) = 0));
        (void)(((module->pending_export) = 0));
        int32_t allow_for_repr_buf = ap_sb;
        if ((pr_sb !=0)) {
          (void)((allow_for_repr_buf = 1));
        }
        int32_t nsl_before_buf = (module->num_struct_layouts);
        if ((parser_parse_struct_record_layout_into_buf(arena, module, lex, data, len, &(lex), allow_for_repr_buf, ps_sb, pc_sb) !=0)) {
          /* wave679: P012 sticky → hard abort (no soft-skip false green). PLATFORM: SHARED */
          {
            extern int32_t parser_sig_type_hard_pending_c(void);
            if (parser_sig_type_hard_pending_c() != 0) {
              return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
            }
          }
          (void)(parser_skip_one_struct_into_buf(&(lex), lex_kw, data, len));
        } else {
          if (((pe_sb !=0) && ((module->num_struct_layouts) > nsl_before_buf))) {
            (void)(pipeline_module_struct_layout_set_is_export(module, ((module->num_struct_layouts) - 1), 1));
          }
        }
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==47)) {
        int32_t pe_enum_buf = (module->pending_export);
        (void)(((module->pending_export) = 0));
        int32_t nen_before_buf = (module->num_module_enums);
        (void)(parser_skip_one_enum_register_into_buf(module, &(lex), iter_start_buf, data, len));
        if (((pe_enum_buf !=0) && ((module->num_module_enums) > nen_before_buf))) {
          (void)(pipeline_module_enum_set_is_export(module, ((module->num_module_enums) - 1), 1));
        }
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==49)) {
        (void)(parser_skip_one_trait_into_buf(&(lex), iter_start_buf, data, len));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==50)) {
        (void)(parser_skip_one_impl_into_buf(&(lex), iter_start_buf, data, len));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        } else {
          (void)((impl_body_depth_buf = (impl_body_depth_buf + 1)));
        }
        continue;
      }
      if ((((r.tok).kind) ==54)) {
        (void)(parser_parse_one_extern_and_add_into_buf(arena, module, iter_start_buf, data, len, &(lex)));
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)(parser_skip_one_extern_into_buf(&(lex), iter_start_buf, data, len));
        }
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==20)) {
        struct parser_TypeAliasResult alias_res = (struct parser_TypeAliasResult){ .ok = 0, .next_lex = lex };
        (void)(parser_parse_one_type_alias_into_buf(arena, module, (r.next_lex), data, len, &(alias_res)));
        if ((alias_res.ok)) {
          (void)((lex = (alias_res.next_lex)));
          continue;
        }
      }
      if (((((r.tok).kind) ==2) || (((r.tok).kind) ==3))) {
        int32_t pe_tl = (module->pending_export);
        (void)(((module->pending_export) = 0));
        int32_t ntl_before = (module->num_top_level_lets);
        struct parser_TopLevelLetResult toplevel_res = (struct parser_TopLevelLetResult){ .ok = 0, .next_lex = lex };
        (void)(parser_parse_one_top_level_let_into_buf(arena, module, (r.next_lex), data, len, (((r.tok).kind) ==3), &(toplevel_res)));
        if ((toplevel_res.ok)) {
          if (((pe_tl !=0) && ((module->num_top_level_lets) > ntl_before))) {
            (void)(pipeline_module_top_level_let_set_is_export(module, ((module->num_top_level_lets) - 1), 1));
          }
          (void)((lex = (toplevel_res.next_lex)));
          continue;
        }
      }
      /* Impl closer after skip_one_impl parked at first method (wave390 UFCS).
       * Without this, parse_strict treats the leftover `}` as unexpected → P001.
       * PLATFORM: SHARED parse. */
      if (((((r.tok).kind) ==85) && (impl_body_depth_buf > 0))) {
        (void)((impl_body_depth_buf = (impl_body_depth_buf - 1)));
        continue;
      }
      if ((((r.tok).kind) !=1)) {
        struct parser_TrySkipAllowResult try_res = (struct parser_TrySkipAllowResult){ .lex = lex, .skipped = 0, ._pad = { 0 } };
        (void)(parser_parse_into_try_skip_allow_into_buf(&(try_res), lex, r, data, len));
        if (((try_res.skipped) !=0)) {
          (void)(((module->pending_allow_padding) = 1));
          (void)(parser_lex_from_try_skip_into(&(lex), try_res));
          if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        if ((((r.tok).kind) ==0)) {
          break;
        }
        /* wave check-false-green (2026-08-05): parse_strict (check) hard-fails unexpected top-level. */
        if (parser_parse_strict_enabled() != 0) {
          (void)(parser_diagnostic_parse_skip(((int32_t)((iter_start_buf.pos))), (module->num_funcs), 0, ((uint8_t *)(0))));
          return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
        }
        if ((((lex.pos) ==(iter_start_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      if ((((r.tok).kind) ==0)) {
        if (((module->num_funcs) ==0)) {
          return parser_parse_into_result_empty_module_or_fail_tok(parser_diag_fail_at_token_kind_buf(data, len));
        }
        /* wave424: trait completeness on freestanding -o (direct parse_into_buf). */
        return parser_parse_into_finish_ok(module, main_idx);
      }
      /* Latch export before body parse (buf path; G.7 ≡ pe_struct). */
      int32_t pe_fn_buf = (module->pending_export);
      (void)(((module->pending_export) = 0));
      struct lexer_Lexer lex_at_function_buf = lexer_init();
      (void)((lex_at_function_buf = current_tok_lex_buf));
      (void)(parser_lex_from_next_into(&(lex), r));
      uint8_t empty64_buf[128] = {};
      struct parser_OneFuncResult res = parser_onefunc_scratch_empty();
      (void)((res = parser_onefunc_scratch_empty()));
      (void)(parser_onefunc_res_wire_dummy_head(&(res), lex, empty64_buf));
      (void)(parser_onefunc_res_wire_dummy_const_let(&(res)));
      (void)(parser_onefunc_res_wire_dummy_if_mul(&(res)));
      (void)(parser_onefunc_res_wire_dummy_call_binop(&(res), empty64_buf));
      (void)(parser_onefunc_res_wire_dummy_loop_call(&(res)));
      (void)(parser_onefunc_res_wire_dummy_for_if(&(res)));
      struct xlang_slice_uint8_t slice_for_impl = parser_slice_from_buf(data, len);
      (void)((slice_for_impl = parser_slice_from_buf(data, len)));
      uint8_t empty64_lib_buf_first[128] = {};
      struct parser_LibraryParseResult lib_buf_first = (struct parser_LibraryParseResult){ .ok = 0, ._pad = { 0 }, .next_lex = lex_at_function_buf, .name = {empty64_lib_buf_first[0], empty64_lib_buf_first[1], empty64_lib_buf_first[2], empty64_lib_buf_first[3], empty64_lib_buf_first[4], empty64_lib_buf_first[5], empty64_lib_buf_first[6], empty64_lib_buf_first[7], empty64_lib_buf_first[8], empty64_lib_buf_first[9], empty64_lib_buf_first[10], empty64_lib_buf_first[11], empty64_lib_buf_first[12], empty64_lib_buf_first[13], empty64_lib_buf_first[14], empty64_lib_buf_first[15], empty64_lib_buf_first[16], empty64_lib_buf_first[17], empty64_lib_buf_first[18], empty64_lib_buf_first[19], empty64_lib_buf_first[20], empty64_lib_buf_first[21], empty64_lib_buf_first[22], empty64_lib_buf_first[23], empty64_lib_buf_first[24], empty64_lib_buf_first[25], empty64_lib_buf_first[26], empty64_lib_buf_first[27], empty64_lib_buf_first[28], empty64_lib_buf_first[29], empty64_lib_buf_first[30], empty64_lib_buf_first[31], empty64_lib_buf_first[32], empty64_lib_buf_first[33], empty64_lib_buf_first[34], empty64_lib_buf_first[35], empty64_lib_buf_first[36], empty64_lib_buf_first[37], empty64_lib_buf_first[38], empty64_lib_buf_first[39], empty64_lib_buf_first[40], empty64_lib_buf_first[41], empty64_lib_buf_first[42], empty64_lib_buf_first[43], empty64_lib_buf_first[44], empty64_lib_buf_first[45], empty64_lib_buf_first[46], empty64_lib_buf_first[47], empty64_lib_buf_first[48], empty64_lib_buf_first[49], empty64_lib_buf_first[50], empty64_lib_buf_first[51], empty64_lib_buf_first[52], empty64_lib_buf_first[53], empty64_lib_buf_first[54], empty64_lib_buf_first[55], empty64_lib_buf_first[56], empty64_lib_buf_first[57], empty64_lib_buf_first[58], empty64_lib_buf_first[59], empty64_lib_buf_first[60], empty64_lib_buf_first[61], empty64_lib_buf_first[62], empty64_lib_buf_first[63]}, .name_len = 0, ._pad_tail = { 0 } };
      (void)((lib_buf_first = (struct parser_LibraryParseResult){ .ok = 0, ._pad = { 0 }, .next_lex = lex_at_function_buf, .name = {empty64_lib_buf_first[0], empty64_lib_buf_first[1], empty64_lib_buf_first[2], empty64_lib_buf_first[3], empty64_lib_buf_first[4], empty64_lib_buf_first[5], empty64_lib_buf_first[6], empty64_lib_buf_first[7], empty64_lib_buf_first[8], empty64_lib_buf_first[9], empty64_lib_buf_first[10], empty64_lib_buf_first[11], empty64_lib_buf_first[12], empty64_lib_buf_first[13], empty64_lib_buf_first[14], empty64_lib_buf_first[15], empty64_lib_buf_first[16], empty64_lib_buf_first[17], empty64_lib_buf_first[18], empty64_lib_buf_first[19], empty64_lib_buf_first[20], empty64_lib_buf_first[21], empty64_lib_buf_first[22], empty64_lib_buf_first[23], empty64_lib_buf_first[24], empty64_lib_buf_first[25], empty64_lib_buf_first[26], empty64_lib_buf_first[27], empty64_lib_buf_first[28], empty64_lib_buf_first[29], empty64_lib_buf_first[30], empty64_lib_buf_first[31], empty64_lib_buf_first[32], empty64_lib_buf_first[33], empty64_lib_buf_first[34], empty64_lib_buf_first[35], empty64_lib_buf_first[36], empty64_lib_buf_first[37], empty64_lib_buf_first[38], empty64_lib_buf_first[39], empty64_lib_buf_first[40], empty64_lib_buf_first[41], empty64_lib_buf_first[42], empty64_lib_buf_first[43], empty64_lib_buf_first[44], empty64_lib_buf_first[45], empty64_lib_buf_first[46], empty64_lib_buf_first[47], empty64_lib_buf_first[48], empty64_lib_buf_first[49], empty64_lib_buf_first[50], empty64_lib_buf_first[51], empty64_lib_buf_first[52], empty64_lib_buf_first[53], empty64_lib_buf_first[54], empty64_lib_buf_first[55], empty64_lib_buf_first[56], empty64_lib_buf_first[57], empty64_lib_buf_first[58], empty64_lib_buf_first[59], empty64_lib_buf_first[60], empty64_lib_buf_first[61], empty64_lib_buf_first[62], empty64_lib_buf_first[63]}, .name_len = 0, ._pad_tail = { 0 } }));
      (void)(parser_parse_one_function_library_into_buf(&(lib_buf_first), arena, module, lex_at_function_buf, data, len));
      if ((lib_buf_first.ok)) {
        (void)(parser_lex_from_library_into(&(lex), lib_buf_first));
        continue;
      }
      (void)(parser_parse_one_function_impl(&(res), arena, lex, &(slice_for_impl)));
      if (!((res.ok))) {
        /* wave676: if P011 already sticky, skip buf retry (avoids double P011 diag). */
        extern int32_t parser_sig_type_hard_pending_c(void);
        if (parser_sig_type_hard_pending_c() == 0) {
          (void)(parser_parse_one_function_buf_into(&(res), arena, lex_at_function_buf, data, len));
        }
      }
      if (!((res.ok))) {
        /* wave676: P011 sticky → hard abort (no soft-skip false green). PLATFORM: SHARED. */
        {
          extern int32_t parser_sig_type_hard_pending_c(void);
          if (parser_sig_type_hard_pending_c() != 0) {
            (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
            return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
          }
        }
        uint8_t skip_name[128] = {0};
        int32_t skip_nlen = parser_parse_peek_function_name_buf(lex_at_function_buf, data, len, &((skip_name)[0]));
        (void)(parser_diagnostic_parse_skip(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), skip_nlen, &((skip_name)[0])));
        /* wave check-false-green (2026-08-05): parse_strict/check hard-fail failed function. */
        if (parser_parse_strict_enabled() != 0) {
          (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
          return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
        }
        (void)(parser_skip_one_function_full_into_buf(&(lex), lex_at_function_buf, data, len));
        (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
        if ((((lex.pos) ==(lex_at_function_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      int32_t is_main_storage[1] = {};
      if (((((((res.name_len) ==4) && (((res.name))[0] ==109)) && (((res.name))[1] ==97)) && (((res.name))[2] ==105)) && (((res.name))[3] ==110))) {
        (void)(((is_main_storage)[0] = 1));
      }
      (void)(parser_diagnostic_parse_func_generic(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), &(((res.name))[0]), (res.name_len), (res.num_generic_params), (is_main_storage)[0]));
      int32_t type_ref = 0;
      (void)((type_ref = (res.func_return_type_ref)));
      if ((type_ref ==0)) {
        (void)((type_ref = ast_ast_arena_type_alloc(arena)));
        if ((type_ref ==0)) {
          (void)(parser_diagnostic_parse_skip(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), (res.name_len), &(((res.name))[0])));
          if (parser_parse_strict_enabled() != 0) {
            (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
            return (struct parser_ParseIntoResult){ .ok = -(2), .main_idx = -(1) };
          }
          (void)(parser_skip_one_function_full_into_buf(&(lex), lex_at_function_buf, data, len));
          (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
          if ((((lex.pos) ==(lex_at_function_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
            (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
          }
          continue;
        }
        struct ast_Type t_fb = ast_ast_arena_type_get(arena, type_ref);
        (void)(((t_fb.kind) = 0));
        (void)(((t_fb.name_len) = 0));
        (void)(((t_fb.elem_type_ref) = 0));
        (void)(((t_fb.array_size) = 0));
        (void)(ast_ast_arena_type_set(arena, type_ref, t_fb));
      }
      int32_t expr_ref = 0;
      (void)((expr_ref = ast_ast_arena_expr_alloc(arena)));
      if ((expr_ref ==0)) {
        (void)(parser_diagnostic_parse_commit_fail(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), (res.name_len), &(((res.name))[0])));
        (void)(parser_skip_one_function_full_into_buf(&(lex), lex_at_function_buf, data, len));
        (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
        if ((((lex.pos) ==(lex_at_function_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      struct ast_Expr e = ast_ast_arena_expr_get(arena, expr_ref);
      (void)((e = ast_ast_arena_expr_get(arena, expr_ref)));
      if (((res.return_var_name_len) > 0)) {
        (void)(((e.kind) = 3));
        (void)(((e.var_name_len) = (res.return_var_name_len)));
        int32_t rvi = 0;
        while (((rvi < (res.return_var_name_len)) && (rvi < 128))) {
          (void)((((e.var_name))[rvi] = ((res.return_var_name))[rvi]));
          (void)((rvi = (rvi + 1)));
        }
        uint8_t rvz = ((uint8_t)(0));
        while ((rvi < 128)) {
          (void)((((e.var_name))[rvi] = rvz));
          (void)((rvi = (rvi + 1)));
        }
        (void)(((e.int_val) = 0));
        (void)(((e.resolved_type_ref) = 0));
      } else {
        (void)(((e.kind) = 0));
        (void)(((e.int_val) = (res.return_val)));
        (void)(((e.resolved_type_ref) = type_ref));
      }
      (void)(((e.line) = 0));
      (void)(((e.col) = 0));
      (void)(((e.binop_left_ref) = 0));
      (void)(((e.binop_right_ref) = 0));
      (void)(((e.unary_operand_ref) = 0));
      (void)(((e.if_cond_ref) = 0));
      (void)(((e.if_then_ref) = 0));
      (void)(((e.if_else_ref) = 0));
      (void)(((e.block_ref) = 0));
      (void)(((e.match_matched_ref) = 0));
      (void)(((e.match_num_arms) = 0));
      (void)(ast_expr_init_match_enum(&(e)));
      (void)(((e.field_access_base_ref) = 0));
      (void)(((e.field_access_field_len) = 0));
      (void)(((e.field_access_is_enum_variant) = 0));
      (void)(((e.field_access_offset) = 0));
      (void)(((e.index_base_ref) = 0));
      (void)(((e.index_index_ref) = 0));
      (void)(((e.index_base_is_slice) = 0));
      (void)(((e.call_callee_ref) = 0));
      (void)(((e.call_num_args) = 0));
      (void)(((e.method_call_base_ref) = 0));
      (void)(((e.method_call_name_len) = 0));
      (void)(((e.method_call_num_args) = 0));
      (void)(((e.const_folded_val) = 0));
      (void)(((e.const_folded_valid) = 0));
      (void)(((e.index_proven_in_bounds) = 0));
      (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
      int allow_legacy_tail_expr2 = 0;
      (void)((allow_legacy_tail_expr2 = ((((res.has_final_expr) || (res.has_explicit_return_kw)) || ((res.return_expr_ref) !=0)) || ((res.return_var_name_len) > 0))));
      int32_t final_expr_ref = 0;
      if (allow_legacy_tail_expr2) {
        (void)((final_expr_ref = expr_ref));
      }
      if (((res.return_expr_ref) !=0)) {
        (void)((final_expr_ref = (res.return_expr_ref)));
      }
      if ((((res.return_var_name_len) > 0) && ((res.return_expr_ref) ==0))) {
        int32_t var_wrapped = parser_expr_wrap_in_return(arena, type_ref, final_expr_ref);
        if ((var_wrapped ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1003) };
        }
        (void)((final_expr_ref = var_wrapped));
      }
      if (((res.has_mul) && !((res.has_binop)))) {
        int32_t mul_right_ref = ast_ast_arena_expr_alloc(arena);
        if ((mul_right_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr mre = ast_ast_arena_expr_get(arena, mul_right_ref);
        (void)(((mre.kind) = 0));
        (void)(((mre.resolved_type_ref) = type_ref));
        (void)(((mre.line) = 0));
        (void)(((mre.col) = 0));
        (void)(((mre.int_val) = (res.mul_right_val)));
        (void)(((mre.binop_left_ref) = 0));
        (void)(((mre.binop_right_ref) = 0));
        (void)(((mre.unary_operand_ref) = 0));
        (void)(((mre.if_cond_ref) = 0));
        (void)(((mre.if_then_ref) = 0));
        (void)(((mre.if_else_ref) = 0));
        (void)(((mre.block_ref) = 0));
        (void)(((mre.match_matched_ref) = 0));
        (void)(((mre.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(mre)));
        (void)(((mre.field_access_base_ref) = 0));
        (void)(((mre.field_access_field_len) = 0));
        (void)(((mre.field_access_is_enum_variant) = 0));
        (void)(((mre.field_access_offset) = 0));
        (void)(((mre.index_base_ref) = 0));
        (void)(((mre.index_index_ref) = 0));
        (void)(((mre.index_base_is_slice) = 0));
        (void)(((mre.call_callee_ref) = 0));
        (void)(((mre.call_num_args) = 0));
        (void)(((mre.method_call_base_ref) = 0));
        (void)(((mre.method_call_name_len) = 0));
        (void)(((mre.method_call_num_args) = 0));
        (void)(((mre.const_folded_val) = 0));
        (void)(((mre.const_folded_valid) = 0));
        (void)(((mre.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, mul_right_ref, mre));
        int32_t mul_ref = ast_ast_arena_expr_alloc(arena);
        if ((mul_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr me = ast_ast_arena_expr_get(arena, mul_ref);
        (void)(((me.kind) = 53));
        (void)(((me.resolved_type_ref) = type_ref));
        (void)(((me.line) = 0));
        (void)(((me.col) = 0));
        (void)(((me.int_val) = 0));
        (void)(((me.binop_left_ref) = expr_ref));
        (void)(((me.binop_right_ref) = mul_right_ref));
        (void)(((me.unary_operand_ref) = 0));
        (void)(((me.if_cond_ref) = 0));
        (void)(((me.if_then_ref) = 0));
        (void)(((me.if_else_ref) = 0));
        (void)(((me.block_ref) = 0));
        (void)(((me.match_matched_ref) = 0));
        (void)(((me.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(me)));
        (void)(((me.field_access_base_ref) = 0));
        (void)(((me.field_access_field_len) = 0));
        (void)(((me.field_access_is_enum_variant) = 0));
        (void)(((me.field_access_offset) = 0));
        (void)(((me.index_base_ref) = 0));
        (void)(((me.index_index_ref) = 0));
        (void)(((me.index_base_is_slice) = 0));
        (void)(((me.call_callee_ref) = 0));
        (void)(((me.call_num_args) = 0));
        (void)(((me.method_call_base_ref) = 0));
        (void)(((me.method_call_name_len) = 0));
        (void)(((me.method_call_num_args) = 0));
        (void)(((me.const_folded_val) = 0));
        (void)(((me.const_folded_valid) = 0));
        (void)(((me.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, mul_ref, me));
        (void)(ast_ast_arena_expr_set(arena, expr_ref, e));
      }
      if ((res.has_if_expr)) {
        int32_t cond_ref = 0;
        if (((res.if_cond_expr_ref) !=0)) {
          (void)((cond_ref = (res.if_cond_expr_ref)));
        } else {
          int32_t bool_type_ref = ast_ast_arena_type_alloc(arena);
          if ((bool_type_ref ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1005) };
          }
          struct ast_Type bt = ast_ast_arena_type_get(arena, bool_type_ref);
          (void)(((bt.kind) = 1));
          (void)(((bt.name_len) = 0));
          (void)(((bt.elem_type_ref) = 0));
          (void)(((bt.array_size) = 0));
          (void)(ast_ast_arena_type_set(arena, bool_type_ref, bt));
          (void)((cond_ref = ast_ast_arena_expr_alloc(arena)));
          if ((cond_ref ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          struct ast_Expr ce = ast_ast_arena_expr_get(arena, cond_ref);
          (void)(((ce.kind) = 2));
          (void)(((ce.resolved_type_ref) = bool_type_ref));
          (void)(((ce.line) = 0));
          (void)(((ce.col) = 0));
          if ((res.if_cond_true)) {
            (void)(((ce.int_val) = 1));
          } else {
            (void)(((ce.int_val) = 0));
          }
          (void)(((ce.binop_left_ref) = 0));
          (void)(((ce.binop_right_ref) = 0));
          (void)(((ce.unary_operand_ref) = 0));
          (void)(((ce.if_cond_ref) = 0));
          (void)(((ce.if_then_ref) = 0));
          (void)(((ce.if_else_ref) = 0));
          (void)(((ce.block_ref) = 0));
          (void)(((ce.match_matched_ref) = 0));
          (void)(((ce.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ce)));
          (void)(((ce.field_access_base_ref) = 0));
          (void)(((ce.field_access_field_len) = 0));
          (void)(((ce.field_access_is_enum_variant) = 0));
          (void)(((ce.field_access_offset) = 0));
          (void)(((ce.index_base_ref) = 0));
          (void)(((ce.index_index_ref) = 0));
          (void)(((ce.index_base_is_slice) = 0));
          (void)(((ce.call_callee_ref) = 0));
          (void)(((ce.call_num_args) = 0));
          (void)(((ce.method_call_base_ref) = 0));
          (void)(((ce.method_call_name_len) = 0));
          (void)(((ce.method_call_num_args) = 0));
          (void)(((ce.const_folded_val) = 0));
          (void)(((ce.const_folded_valid) = 0));
          (void)(((ce.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, cond_ref, ce));
        }
        int32_t then_ref = ast_ast_arena_expr_alloc(arena);
        if ((then_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr te = ast_ast_arena_expr_get(arena, then_ref);
        (void)(((te.kind) = 0));
        (void)(((te.resolved_type_ref) = type_ref));
        (void)(((te.line) = 0));
        (void)(((te.col) = 0));
        (void)(((te.int_val) = (res.if_then_val)));
        (void)(((te.binop_left_ref) = 0));
        (void)(((te.binop_right_ref) = 0));
        (void)(((te.unary_operand_ref) = 0));
        (void)(((te.if_cond_ref) = 0));
        (void)(((te.if_then_ref) = 0));
        (void)(((te.if_else_ref) = 0));
        (void)(((te.block_ref) = 0));
        (void)(((te.match_matched_ref) = 0));
        (void)(((te.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(te)));
        (void)(((te.field_access_base_ref) = 0));
        (void)(((te.field_access_field_len) = 0));
        (void)(((te.field_access_is_enum_variant) = 0));
        (void)(((te.field_access_offset) = 0));
        (void)(((te.index_base_ref) = 0));
        (void)(((te.index_index_ref) = 0));
        (void)(((te.index_base_is_slice) = 0));
        (void)(((te.call_callee_ref) = 0));
        (void)(((te.call_num_args) = 0));
        (void)(((te.method_call_base_ref) = 0));
        (void)(((te.method_call_name_len) = 0));
        (void)(((te.method_call_num_args) = 0));
        (void)(((te.const_folded_val) = 0));
        (void)(((te.const_folded_valid) = 0));
        (void)(((te.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, then_ref, te));
        int32_t else_ref = ast_ast_arena_expr_alloc(arena);
        if ((else_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr ee = ast_ast_arena_expr_get(arena, else_ref);
        (void)(((ee.kind) = 0));
        (void)(((ee.resolved_type_ref) = type_ref));
        (void)(((ee.line) = 0));
        (void)(((ee.col) = 0));
        (void)(((ee.int_val) = (res.if_else_val)));
        (void)(((ee.binop_left_ref) = 0));
        (void)(((ee.binop_right_ref) = 0));
        (void)(((ee.unary_operand_ref) = 0));
        (void)(((ee.if_cond_ref) = 0));
        (void)(((ee.if_then_ref) = 0));
        (void)(((ee.if_else_ref) = 0));
        (void)(((ee.block_ref) = 0));
        (void)(((ee.match_matched_ref) = 0));
        (void)(((ee.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(ee)));
        (void)(((ee.field_access_base_ref) = 0));
        (void)(((ee.field_access_field_len) = 0));
        (void)(((ee.field_access_is_enum_variant) = 0));
        (void)(((ee.field_access_offset) = 0));
        (void)(((ee.index_base_ref) = 0));
        (void)(((ee.index_index_ref) = 0));
        (void)(((ee.index_base_is_slice) = 0));
        (void)(((ee.call_callee_ref) = 0));
        (void)(((ee.call_num_args) = 0));
        (void)(((ee.method_call_base_ref) = 0));
        (void)(((ee.method_call_name_len) = 0));
        (void)(((ee.method_call_num_args) = 0));
        (void)(((ee.const_folded_val) = 0));
        (void)(((ee.const_folded_valid) = 0));
        (void)(((ee.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, else_ref, ee));
        int32_t if_expr_ref = ast_ast_arena_expr_alloc(arena);
        if ((if_expr_ref ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        struct ast_Expr ie = ast_ast_arena_expr_get(arena, if_expr_ref);
        (void)(((ie.kind) = 25));
        (void)(((ie.resolved_type_ref) = type_ref));
        (void)(((ie.line) = 0));
        (void)(((ie.col) = 0));
        (void)(((ie.int_val) = 0));
        (void)(((ie.binop_left_ref) = 0));
        (void)(((ie.binop_right_ref) = 0));
        (void)(((ie.unary_operand_ref) = 0));
        (void)(((ie.if_cond_ref) = cond_ref));
        (void)(((ie.if_then_ref) = then_ref));
        (void)(((ie.if_else_ref) = else_ref));
        (void)(((ie.block_ref) = 0));
        (void)(((ie.match_matched_ref) = 0));
        (void)(((ie.match_num_arms) = 0));
        (void)(ast_expr_init_match_enum(&(ie)));
        (void)(((ie.field_access_base_ref) = 0));
        (void)(((ie.field_access_field_len) = 0));
        (void)(((ie.field_access_is_enum_variant) = 0));
        (void)(((ie.field_access_offset) = 0));
        (void)(((ie.index_base_ref) = 0));
        (void)(((ie.index_index_ref) = 0));
        (void)(((ie.index_base_is_slice) = 0));
        (void)(((ie.call_callee_ref) = 0));
        (void)(((ie.call_num_args) = 0));
        (void)(((ie.method_call_base_ref) = 0));
        (void)(((ie.method_call_name_len) = 0));
        (void)(((ie.method_call_num_args) = 0));
        (void)(((ie.const_folded_val) = 0));
        (void)(((ie.const_folded_valid) = 0));
        (void)(((ie.index_proven_in_bounds) = 0));
        (void)(ast_ast_arena_expr_set(arena, if_expr_ref, ie));
        (void)((final_expr_ref = if_expr_ref));
      }
      if (((res.return_expr_ref) ==0)) {
        if (((res.has_binop) || ((res.binop_right_val) !=0))) {
          uint8_t * res_pool_buf = parser_onefunc_result_pool_ptr(&(res));
          int32_t left_ref_buf = final_expr_ref;
          if ((((res.binop_left_param_idx) >=0) && ((res.binop_left_param_idx) < (res.num_params)))) {
            int32_t left_param_type_ref_buf = pipeline_onefunc_param_type_ref(res_pool_buf, (res.binop_left_param_idx));
            int32_t lpr_buf = ast_ast_arena_expr_alloc(arena);
            if ((lpr_buf !=0)) {
              struct ast_Expr lpe_buf = ast_ast_arena_expr_get(arena, lpr_buf);
              (void)(((lpe_buf.kind) = 3));
              (void)(((lpe_buf.resolved_type_ref) = left_param_type_ref_buf));
              (void)(((lpe_buf.line) = 0));
              (void)(((lpe_buf.col) = 0));
              (void)(((lpe_buf.var_name_len) = pipeline_onefunc_param_name_len(res_pool_buf, (res.binop_left_param_idx))));
              int32_t lk_buf = 0;
              while (((lk_buf < (lpe_buf.var_name_len)) && (lk_buf < 64))) {
                (void)((((lpe_buf.var_name))[lk_buf] = pipeline_onefunc_param_name_byte_at(res_pool_buf, (res.binop_left_param_idx), lk_buf)));
                (void)((lk_buf = (lk_buf + 1)));
              }
              uint8_t lz_buf = ((uint8_t)(0));
              while ((lk_buf < 64)) {
                (void)((((lpe_buf.var_name))[lk_buf] = lz_buf));
                (void)((lk_buf = (lk_buf + 1)));
              }
              (void)(((lpe_buf.binop_left_ref) = 0));
              (void)(((lpe_buf.binop_right_ref) = 0));
              (void)(((lpe_buf.unary_operand_ref) = 0));
              (void)(((lpe_buf.if_cond_ref) = 0));
              (void)(((lpe_buf.if_then_ref) = 0));
              (void)(((lpe_buf.if_else_ref) = 0));
              (void)(((lpe_buf.block_ref) = 0));
              (void)(((lpe_buf.match_matched_ref) = 0));
              (void)(((lpe_buf.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(lpe_buf)));
              (void)(((lpe_buf.field_access_base_ref) = 0));
              (void)(((lpe_buf.field_access_field_len) = 0));
              (void)(((lpe_buf.field_access_is_enum_variant) = 0));
              (void)(((lpe_buf.field_access_offset) = 0));
              (void)(((lpe_buf.index_base_ref) = 0));
              (void)(((lpe_buf.index_index_ref) = 0));
              (void)(((lpe_buf.index_base_is_slice) = 0));
              (void)(((lpe_buf.call_callee_ref) = 0));
              (void)(((lpe_buf.call_num_args) = 0));
              (void)(((lpe_buf.method_call_base_ref) = 0));
              (void)(((lpe_buf.method_call_name_len) = 0));
              (void)(((lpe_buf.method_call_num_args) = 0));
              (void)(((lpe_buf.const_folded_val) = 0));
              (void)(((lpe_buf.const_folded_valid) = 0));
              (void)(((lpe_buf.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, lpr_buf, lpe_buf));
              (void)((left_ref_buf = lpr_buf));
            }
          }
          int32_t right_ref_buf = 0;
          if ((((res.binop_right_param_idx) >=0) && ((res.binop_right_param_idx) < (res.num_params)))) {
            int32_t right_param_type_ref_buf = pipeline_onefunc_param_type_ref(res_pool_buf, (res.binop_right_param_idx));
            int32_t rpr_buf = ast_ast_arena_expr_alloc(arena);
            if ((rpr_buf !=0)) {
              struct ast_Expr rpe_buf = ast_ast_arena_expr_get(arena, rpr_buf);
              (void)(((rpe_buf.kind) = 3));
              (void)(((rpe_buf.resolved_type_ref) = right_param_type_ref_buf));
              (void)(((rpe_buf.line) = 0));
              (void)(((rpe_buf.col) = 0));
              (void)(((rpe_buf.var_name_len) = pipeline_onefunc_param_name_len(res_pool_buf, (res.binop_right_param_idx))));
              int32_t rk_buf = 0;
              while (((rk_buf < (rpe_buf.var_name_len)) && (rk_buf < 64))) {
                (void)((((rpe_buf.var_name))[rk_buf] = pipeline_onefunc_param_name_byte_at(res_pool_buf, (res.binop_right_param_idx), rk_buf)));
                (void)((rk_buf = (rk_buf + 1)));
              }
              uint8_t rz_buf = ((uint8_t)(0));
              while ((rk_buf < 64)) {
                (void)((((rpe_buf.var_name))[rk_buf] = rz_buf));
                (void)((rk_buf = (rk_buf + 1)));
              }
              (void)(((rpe_buf.binop_left_ref) = 0));
              (void)(((rpe_buf.binop_right_ref) = 0));
              (void)(((rpe_buf.unary_operand_ref) = 0));
              (void)(((rpe_buf.if_cond_ref) = 0));
              (void)(((rpe_buf.if_then_ref) = 0));
              (void)(((rpe_buf.if_else_ref) = 0));
              (void)(((rpe_buf.block_ref) = 0));
              (void)(((rpe_buf.match_matched_ref) = 0));
              (void)(((rpe_buf.match_num_arms) = 0));
              (void)(ast_expr_init_match_enum(&(rpe_buf)));
              (void)(((rpe_buf.field_access_base_ref) = 0));
              (void)(((rpe_buf.field_access_field_len) = 0));
              (void)(((rpe_buf.field_access_is_enum_variant) = 0));
              (void)(((rpe_buf.field_access_offset) = 0));
              (void)(((rpe_buf.index_base_ref) = 0));
              (void)(((rpe_buf.index_index_ref) = 0));
              (void)(((rpe_buf.index_base_is_slice) = 0));
              (void)(((rpe_buf.call_callee_ref) = 0));
              (void)(((rpe_buf.call_num_args) = 0));
              (void)(((rpe_buf.method_call_base_ref) = 0));
              (void)(((rpe_buf.method_call_name_len) = 0));
              (void)(((rpe_buf.method_call_num_args) = 0));
              (void)(((rpe_buf.const_folded_val) = 0));
              (void)(((rpe_buf.const_folded_valid) = 0));
              (void)(((rpe_buf.index_proven_in_bounds) = 0));
              (void)(ast_ast_arena_expr_set(arena, rpr_buf, rpe_buf));
              (void)((right_ref_buf = rpr_buf));
            }
          } else {
            (void)((right_ref_buf = ast_ast_arena_expr_alloc(arena)));
            if ((right_ref_buf ==0)) {
              return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
            }
            struct ast_Expr re_buf = ast_ast_arena_expr_get(arena, right_ref_buf);
            (void)(((re_buf.kind) = 0));
            (void)(((re_buf.resolved_type_ref) = type_ref));
            (void)(((re_buf.line) = 0));
            (void)(((re_buf.col) = 0));
            (void)(((re_buf.int_val) = (res.binop_right_val)));
            (void)(((re_buf.binop_left_ref) = 0));
            (void)(((re_buf.binop_right_ref) = 0));
            (void)(((re_buf.unary_operand_ref) = 0));
            (void)(((re_buf.if_cond_ref) = 0));
            (void)(((re_buf.if_then_ref) = 0));
            (void)(((re_buf.if_else_ref) = 0));
            (void)(((re_buf.block_ref) = 0));
            (void)(((re_buf.match_matched_ref) = 0));
            (void)(((re_buf.match_num_arms) = 0));
            (void)(ast_expr_init_match_enum(&(re_buf)));
            (void)(((re_buf.field_access_base_ref) = 0));
            (void)(((re_buf.field_access_field_len) = 0));
            (void)(((re_buf.field_access_is_enum_variant) = 0));
            (void)(((re_buf.field_access_offset) = 0));
            (void)(((re_buf.index_base_ref) = 0));
            (void)(((re_buf.index_index_ref) = 0));
            (void)(((re_buf.index_base_is_slice) = 0));
            (void)(((re_buf.call_callee_ref) = 0));
            (void)(((re_buf.call_num_args) = 0));
            (void)(((re_buf.method_call_base_ref) = 0));
            (void)(((re_buf.method_call_name_len) = 0));
            (void)(((re_buf.method_call_num_args) = 0));
            (void)(((re_buf.const_folded_val) = 0));
            (void)(((re_buf.const_folded_valid) = 0));
            (void)(((re_buf.index_proven_in_bounds) = 0));
            (void)(ast_ast_arena_expr_set(arena, right_ref_buf, re_buf));
          }
          int32_t add_ref_buf = ast_ast_arena_expr_alloc(arena);
          if ((add_ref_buf ==0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          struct ast_Expr ae_buf = ast_ast_arena_expr_get(arena, add_ref_buf);
          (void)(((ae_buf.kind) = 4));
          (void)(((ae_buf.resolved_type_ref) = type_ref));
          (void)(((ae_buf.line) = 0));
          (void)(((ae_buf.col) = 0));
          (void)(((ae_buf.int_val) = 0));
          (void)(((ae_buf.binop_left_ref) = left_ref_buf));
          (void)(((ae_buf.binop_right_ref) = right_ref_buf));
          (void)(((ae_buf.unary_operand_ref) = 0));
          (void)(((ae_buf.if_cond_ref) = 0));
          (void)(((ae_buf.if_then_ref) = 0));
          (void)(((ae_buf.if_else_ref) = 0));
          (void)(((ae_buf.block_ref) = 0));
          (void)(((ae_buf.match_matched_ref) = 0));
          (void)(((ae_buf.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ae_buf)));
          (void)(((ae_buf.field_access_base_ref) = 0));
          (void)(((ae_buf.field_access_field_len) = 0));
          (void)(((ae_buf.field_access_is_enum_variant) = 0));
          (void)(((ae_buf.field_access_offset) = 0));
          (void)(((ae_buf.index_base_ref) = 0));
          (void)(((ae_buf.index_index_ref) = 0));
          (void)(((ae_buf.index_base_is_slice) = 0));
          (void)(((ae_buf.call_callee_ref) = 0));
          (void)(((ae_buf.call_num_args) = 0));
          (void)(((ae_buf.method_call_base_ref) = 0));
          (void)(((ae_buf.method_call_name_len) = 0));
          (void)(((ae_buf.method_call_num_args) = 0));
          (void)(((ae_buf.const_folded_val) = 0));
          (void)(((ae_buf.const_folded_valid) = 0));
          (void)(((ae_buf.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, add_ref_buf, ae_buf));
          (void)((final_expr_ref = add_ref_buf));
        }
      }
      if (((((res.has_call_expr) && ((res.return_expr_ref) ==0)) && ((res.call_callee_len) > 0)) && ((res.call_callee_len) <=127))) {
        uint8_t * call_pool_buf = parser_onefunc_result_pool_ptr(&(res));
        int32_t callee_ref = ast_ast_arena_expr_alloc(arena);
        if ((callee_ref !=0)) {
          struct ast_Expr ve = ast_ast_arena_expr_get(arena, callee_ref);
          (void)(((ve.kind) = 3));
          (void)(((ve.resolved_type_ref) = 0));
          (void)(((ve.line) = 0));
          (void)(((ve.col) = 0));
          (void)(((ve.var_name_len) = (res.call_callee_len)));
          int32_t ck = 0;
          while (((ck < (res.call_callee_len)) && (ck < 128))) {
            (void)((((ve.var_name))[ck] = ((res.call_callee_name))[ck]));
            (void)((ck = (ck + 1)));
          }
          uint8_t z = ((uint8_t)(0));
          while ((ck < 128)) {
            (void)((((ve.var_name))[ck] = z));
            (void)((ck = (ck + 1)));
          }
          (void)(((ve.binop_left_ref) = 0));
          (void)(((ve.binop_right_ref) = 0));
          (void)(((ve.unary_operand_ref) = 0));
          (void)(((ve.if_cond_ref) = 0));
          (void)(((ve.if_then_ref) = 0));
          (void)(((ve.if_else_ref) = 0));
          (void)(((ve.block_ref) = 0));
          (void)(((ve.match_matched_ref) = 0));
          (void)(((ve.match_num_arms) = 0));
          (void)(ast_expr_init_match_enum(&(ve)));
          (void)(((ve.field_access_base_ref) = 0));
          (void)(((ve.field_access_field_len) = 0));
          (void)(((ve.field_access_is_enum_variant) = 0));
          (void)(((ve.field_access_offset) = 0));
          (void)(((ve.index_base_ref) = 0));
          (void)(((ve.index_index_ref) = 0));
          (void)(((ve.index_base_is_slice) = 0));
          (void)(((ve.call_callee_ref) = 0));
          (void)(((ve.call_num_args) = 0));
          (void)(((ve.method_call_base_ref) = 0));
          (void)(((ve.method_call_name_len) = 0));
          (void)(((ve.method_call_num_args) = 0));
          (void)(((ve.const_folded_val) = 0));
          (void)(((ve.const_folded_valid) = 0));
          (void)(((ve.index_proven_in_bounds) = 0));
          (void)(ast_ast_arena_expr_set(arena, callee_ref, ve));
          int32_t call_ref = ast_ast_arena_expr_alloc(arena);
          if ((call_ref !=0)) {
            struct ast_Expr ce = ast_ast_arena_expr_get(arena, call_ref);
            (void)(parser_expr_set_common_zeros(&(ce)));
            (void)(((ce.kind) = 48));
            (void)(((ce.resolved_type_ref) = type_ref));
            (void)(((ce.line) = 0));
            (void)(((ce.col) = 0));
            (void)(((ce.call_callee_ref) = callee_ref));
            if (((res.call_num_args) > 0)) {
              (void)(((ce.call_num_args) = (res.call_num_args)));
            } else {
              (void)(((ce.call_num_args) = (res.num_params)));
            }
            (void)(ast_ast_arena_expr_set(arena, call_ref, ce));
            int32_t arg_i = 0;
            while ((arg_i < (ce.call_num_args))) {
              int32_t arg_ref = ast_ast_arena_expr_alloc(arena);
              if ((arg_ref !=0)) {
                struct ast_Expr ae = ast_ast_arena_expr_get(arena, arg_ref);
                (void)(((ae.resolved_type_ref) = 0));
                (void)(((ae.line) = 0));
                (void)(((ae.col) = 0));
                if ((((res.call_num_args) > 0) && (arg_i < (res.call_num_args)))) {
                  (void)(((ae.kind) = 0));
                  (void)(((ae.int_val) = pipeline_onefunc_call_arg_val_at(call_pool_buf, arg_i)));
                } else {
                  (void)(((ae.kind) = 3));
                  (void)(((ae.var_name_len) = pipeline_onefunc_param_name_len(call_pool_buf, arg_i)));
                  int32_t k = 0;
                  while (((k < (ae.var_name_len)) && (k < 128))) {
                    (void)((((ae.var_name))[k] = pipeline_onefunc_param_name_byte_at(call_pool_buf, arg_i, k)));
                    (void)((k = (k + 1)));
                  }
                  uint8_t z = ((uint8_t)(0));
                  while ((k < 64)) {
                    (void)((((ae.var_name))[k] = z));
                    (void)((k = (k + 1)));
                  }
                }
                (void)(parser_expr_set_common_zeros(&(ae)));
                (void)(ast_ast_arena_expr_set(arena, arg_ref, ae));
                (void)(pipeline_expr_append_call_arg(arena, call_ref, arg_ref));
              }
              (void)((arg_i = (arg_i + 1)));
            }
            (void)(((res.return_expr_ref) = call_ref));
            (void)((final_expr_ref = call_ref));
          }
        }
      }
      int32_t block_ref = 0;
      (void)((block_ref = ast_ast_arena_block_alloc(arena)));
      if ((block_ref ==0)) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
      }
      struct ast_Block b = ast_ast_arena_block_get(arena, block_ref);
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(((b.num_consts) = 0));
      (void)(((b.num_lets) = 0));
      (void)(((b.num_early_lets) = 0));
      (void)(((b.num_loops) = 0));
      (void)(((b.num_for_loops) = 0));
      (void)(((b.num_if_stmts) = 0));
      (void)(((b.num_regions) = 0));
      (void)(((b.num_defers) = 0));
      (void)(((b.num_labeled_stmts) = 0));
      (void)(((b.num_expr_stmts) = 0));
      (void)(((b.final_expr_ref) = 0));
      (void)(((b.num_stmt_order) = 0));
      (void)(((b.parent_block_ref) = 0));
      (void)(ast_ast_arena_block_set(arena, block_ref, b));
      if (parser_should_wrap_func_tail_in_return(arena, &(res), type_ref)) {
        int32_t wrapped_tail2 = parser_expr_wrap_in_return(arena, type_ref, final_expr_ref);
        if ((wrapped_tail2 ==0)) {
          return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
        }
        (void)((final_expr_ref = wrapped_tail2));
      }
      (void)(parser_diagnostic_parse_commit_pre(arena, &(((res.name))[0]), (res.name_len), block_ref, parser_onefunc_result_pool_ptr(&(res)), final_expr_ref));
      if (!(parser_fill_block_const_let_from_res(arena, block_ref, &(res), type_ref))) {
        return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      int32_t n_while_pool2 = 0;
      (void)((n_while_pool2 = pipeline_onefunc_num_whiles(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_loops) = n_while_pool2));
      (void)(pipeline_block_fill_whiles_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_while_pool2));
      int32_t n_for_pool2 = 0;
      (void)((n_for_pool2 = pipeline_onefunc_num_fors(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_for_loops) = n_for_pool2));
      (void)(pipeline_block_fill_fors_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_for_pool2));
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      int32_t n_if_pool2 = 0;
      (void)((n_if_pool2 = pipeline_onefunc_num_if_stmts(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(((res.num_if_stmts) = n_if_pool2));
      (void)(pipeline_block_fill_ifs_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_if_pool2));
      int32_t n_reg_pool2 = 0;
      (void)((n_reg_pool2 = pipeline_onefunc_num_regions(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(pipeline_block_fill_regions_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_reg_pool2));
      int32_t n_def_pool2 = 0;
      (void)((n_def_pool2 = pipeline_onefunc_num_defers(parser_onefunc_result_pool_ptr(&(res)))));
      (void)(pipeline_block_fill_defers_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_def_pool2));
      /* wave379: labeled/goto before stmt_order kind=7 */
      {
        int32_t n_lab_pool2 = 0;
        (void)((n_lab_pool2 = pipeline_onefunc_num_labeleds(parser_onefunc_result_pool_ptr(&(res)))));
        (void)(pipeline_block_fill_labeled_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), n_lab_pool2));
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      if (((res.num_src_stmt_order) > 0)) {
        (void)(pipeline_block_fill_expr_stmts_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), pipeline_onefunc_num_body_expr_stmts(parser_onefunc_result_pool_ptr(&(res)))));
        (void)(pipeline_block_fill_stmt_order_from_onefunc(arena, block_ref, parser_onefunc_result_pool_ptr(&(res)), pipeline_onefunc_num_src_stmt_order(parser_onefunc_result_pool_ptr(&(res)))));
        (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      } else {
        int32_t ci2b = 0;
        while ((ci2b < (b.num_consts))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 0, ci2b) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((ci2b = (ci2b + 1)));
        }
        int32_t li2b = 0;
        while ((li2b < (b.num_lets))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 1, li2b) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((li2b = (li2b + 1)));
        }
        int32_t loop_ib = 0;
        while ((loop_ib < (b.num_loops))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 3, loop_ib) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((loop_ib = (loop_ib + 1)));
        }
        int32_t for_ib = 0;
        while ((for_ib < (b.num_for_loops))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 4, for_ib) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((for_ib = (for_ib + 1)));
        }
        int32_t if_oib = 0;
        while ((if_oib < (b.num_if_stmts))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 5, if_oib) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((if_oib = (if_oib + 1)));
        }
        int32_t reg_oib = 0;
        while ((reg_oib < pipeline_onefunc_num_regions(parser_onefunc_result_pool_ptr(&(res))))) {
          if ((pipeline_block_append_stmt_order(arena, block_ref, 6, reg_oib) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((reg_oib = (reg_oib + 1)));
        }
        if ((!(ast_ref_is_null(final_expr_ref)) && ((b.num_expr_stmts) ==0))) {
          int32_t fin_ex2 = pipeline_block_append_expr_stmt(arena, block_ref, final_expr_ref);
          if ((fin_ex2 < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)(((b.final_expr_ref) = 0));
          (void)((final_expr_ref = 0));
          if ((pipeline_block_append_stmt_order(arena, block_ref, 2, fin_ex2) < 0)) {
            return (struct parser_ParseIntoResult){ .ok = -(1), .main_idx = -(1) };
          }
          (void)((b = ast_ast_arena_block_get(arena, block_ref)));
        }
      }
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(((b.final_expr_ref) = final_expr_ref));
      if ((((b.num_expr_stmts) > 0) && !(ast_ref_is_null(final_expr_ref)))) {
        struct ast_Expr fe_dedup2 = ast_ast_arena_expr_get(arena, final_expr_ref);
        if (((fe_dedup2.kind) !=41)) {
          (void)(((b.final_expr_ref) = 0));
        }
      }
      (void)(ast_ast_arena_block_set(arena, block_ref, b));
      (void)(pipeline_block_with_arena_fixup_stmt_order(arena, block_ref));
      (void)((b = ast_ast_arena_block_get(arena, block_ref)));
      (void)(parser_diagnostic_parse_commit_post(arena, &(((res.name))[0]), (res.name_len), block_ref, parser_onefunc_result_pool_ptr(&(res))));
      int32_t func_ref = 0;
      (void)((func_ref = ast_ast_arena_func_alloc(arena)));
      if ((func_ref ==0)) {
        (void)(parser_diagnostic_parse_commit_fail(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), (res.name_len), &(((res.name))[0])));
        (void)(parser_skip_one_function_full_into_buf(&(lex), lex_at_function_buf, data, len));
        (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
        if ((((lex.pos) ==(lex_at_function_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      int32_t fi_mod = -(1);
      (void)((fi_mod = pipeline_module_func_alloc_slot(module)));
      if ((fi_mod < 0)) {
        (void)(parser_diagnostic_parse_commit_fail(((int32_t)((lex_at_function_buf.pos))), (module->num_funcs), (res.name_len), &(((res.name))[0])));
        (void)(parser_skip_one_function_full_into_buf(&(lex), lex_at_function_buf, data, len));
        (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
        if ((((lex.pos) ==(lex_at_function_buf.pos)) && ((lex.pos) < ((size_t)(len))))) {
          (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
        }
        continue;
      }
      (void)(pipeline_module_func_name_write(module, fi_mod, &(((res.name))[0]), (res.name_len)));
      (void)(pipeline_module_func_set_num_params(module, fi_mod, (res.num_params)));
      (void)(pipeline_module_func_set_num_generic_params(module, fi_mod, (res.num_generic_params)));
      /* Cap 10.7.1: OneFuncResult.is_variadic → module Func buf path (≡ parser.x). */
      (void)(pipeline_module_func_set_is_variadic(module, fi_mod, (res.is_variadic)));
      (void)(pipeline_module_func_set_return_type(module, fi_mod, type_ref));
      (void)(pipeline_module_func_set_body_ref(module, fi_mod, block_ref));
      (void)(pipeline_module_func_set_body_expr_ref(module, fi_mod, 0));
      (void)(pipeline_module_func_set_is_extern(module, fi_mod, 0));
      (void)(pipeline_module_func_set_is_async(module, fi_mod, (func_is_async_buf)[0]));
      (void)(pipeline_module_func_set_is_export(module, fi_mod, pe_fn_buf));
      (void)(pipeline_module_func_set_is_used(module, fi_mod, (module->pending_used)));
      (void)(((module->pending_used) = 0));
      (void)(pipeline_module_func_set_is_naked(module, fi_mod, (module->pending_naked)));
      (void)(((module->pending_naked) = 0));
      (void)(pipeline_module_func_set_is_entry(module, fi_mod, (module->pending_entry)));
      (void)(((module->pending_entry) = 0));
      (void)(pipeline_module_func_set_is_no_mangle(module, fi_mod, (module->pending_no_mangle)));
      (void)(((module->pending_no_mangle) = 0));
      (void)(pipeline_module_func_set_is_interrupt(module, fi_mod, (module->pending_interrupt)));
      (void)(((module->pending_interrupt) = 0));
      int32_t p_copy = 0;
      uint8_t * mod_pool_buf = parser_onefunc_result_pool_ptr(&(res));
      while ((p_copy < (res.num_params))) {
        uint8_t pname32b[128] = {};
        (void)(pipeline_onefunc_param_name_copy32(mod_pool_buf, p_copy, &((pname32b)[0])));
        (void)(pipeline_module_func_param_write(module, fi_mod, p_copy, &((pname32b)[0]), pipeline_onefunc_param_name_len(mod_pool_buf, p_copy), pipeline_onefunc_param_type_ref(mod_pool_buf, p_copy)));
        (void)((p_copy = (p_copy + 1)));
      }
      (void)(pipeline_module_func_ref_set(module, fi_mod, func_ref));
      (void)(pipeline_arena_func_copy_slot_from_module(arena, func_ref, module, fi_mod));
      if (((is_main_storage)[0] !=0)) {
        (void)((main_idx = fi_mod));
      }
      size_t parse_into_guard_pos = (lex.pos);
      (void)(parser_lex_from_onefunc_next_into(&(lex), &(res)));
      (void)(ast_pool_onefunc_release(parser_onefunc_result_pool_ptr(&(res))));
      if (((lex.pos) ==parse_into_guard_pos)) {
        (void)((lex = (struct lexer_Lexer){ .pos = ((lex.pos) + 1), .line = (lex.line), .col = ((lex.col) + 1) }));
      }
    }
    if (((module->num_funcs) ==0)) {
      return parser_parse_into_result_empty_module_or_fail_tok(parser_diag_fail_at_token_kind_buf(data, len));
    }
    /* wave424: trait completeness on freestanding -o (direct parse_into_buf). */
    return parser_parse_into_finish_ok(module, main_idx);
  }
}
extern void parser_parse_into_set_main_index_glue(struct ast_Module * module, int32_t main_idx);
void parser_parse_into_set_main_index(struct ast_Module * module, int32_t main_idx) {
  (void)(parser_parse_into_set_main_index_glue(module, main_idx));
}
extern int32_t parser_diag_token_after_collect_imports_glue(struct xlang_slice_uint8_t * source, struct ast_Module * module);
int32_t parser_diag_token_after_collect_imports(struct xlang_slice_uint8_t * source, struct ast_Module * module) {
  return parser_diag_token_after_collect_imports_glue(source, module);
  return 0;
}
extern int32_t parser_diag_parse_one_after_collect_imports_glue(struct xlang_slice_uint8_t * source, struct ast_Module * module, struct ast_ASTArena * arena);
int32_t parser_diag_parse_one_after_collect_imports(struct xlang_slice_uint8_t * source, struct ast_Module * module, struct ast_ASTArena * arena) {
  return parser_diag_parse_one_after_collect_imports_glue(source, module, arena);
  return 0;
}
extern int32_t parser_parse_one_function_ok_for_pipeline_glue(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source);
int32_t parser_parse_one_function_ok_for_pipeline(struct ast_ASTArena * arena, struct xlang_slice_uint8_t * source) {
  return parser_parse_one_function_ok_for_pipeline_glue(arena, source);
  return 0;
}
int32_t parser_get_module_num_imports(struct ast_Module * module) {
  return (module->num_imports);
}
void parser_get_module_import_path(struct ast_Module * module, int32_t i, uint8_t * out) {
  if (((i < 0) || (i >=(module->num_imports)))) {
    uint8_t z = ((uint8_t)(0));
    (void)(((out)[0] = z));
    return;
  }
  (void)(pipeline_module_import_path_copy(module, i, &((out)[0]), 64));
}
/* wave99: product pure owns parser_copy_module_import_path64 (runtime_pipeline_abi.x).
 * Keep body as XLANG_WEAK cold twin so hybrid PREFER pure wins; cold/non-PREFER still works.
 * PLATFORM: SHARED — semantics ≡ pure (get_path + NUL scan). */
__attribute__((weak)) int32_t parser_copy_module_import_path64(struct ast_Module * module, int32_t i, uint8_t * out) {
  {
    (void)(parser_get_module_import_path(module, i, out));
    int32_t path_len = 0;
    while (((path_len < 64) && ((out)[path_len] !=0))) {
      (void)((path_len = (path_len + 1)));
    }
    return path_len;
  }
}
/* stripped: parser.x export main harness (not for product link) */
/* wave312 G.7: monofile dual WEAK polyfills → extern-only (n=29).
 * Live STRONG = runtime / product .o; ban dual T on host-cc mega gen .o.
 * PLATFORM: SHARED freestanding mega gen seed dual leave.
 */
