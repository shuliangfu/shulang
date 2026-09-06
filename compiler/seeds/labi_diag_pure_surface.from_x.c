/* seeds/labi_diag_pure_surface.from_x.c
 * G-02f labi_diag_pure R2 full surface — isomorphic with src/runtime/labi_diag_pure.x
 * Product PREFER_X_O: g05_try_x_to_o(labi_diag_pure.x) + mega rest under FROM_X
 * Prove: full.x vs this seed → nm IDENTICAL (code_for_kind + reports + count + wave111/112/113/216/217/219/220/222)
 * Cap residual: link_diag_ld_debug_argv → mega _impl (char**);
 *   link_diag_strerror_current_impl (errno+strerror; wave217);
 *   link_diag_wait_*_impl (WIF*; wave217);
 *   xlang_waitpid_retry_impl (waitpid+EINTR+strerror; wave216);
 *   xlang_spawn_sync_impl (fork/exec/wait or _spawnvp; wave219);
 *   invoke_cc_strip_out_x_impl (strip argv pack + spawn; wave220);
 *   link_abi_getenv_impl (host getenv; wave222);
 *   link_abi_system_impl (host system; wave224);
 *   wave111 perror; wave112 tool/obj status; wave113 errno/_path pure orch;
 *   wave217 strerror_current + wait_* pure thin; wave219 spawn_sync pure thin;
 *   wave220 strip_out_x pure thin; wave222 getenv pure thin; wave224 system pure thin
 * Regen: ./xlang -E ... src/runtime/labi_diag_pure.x | filter DBG + polish prologue
 * Track-L (2026-07-16): labi_diag_append keeps short name; .x has #[no_mangle] (was module mangle).
 * PLATFORM: SHARED — symbol contract; Ubuntu gold + mac prove.
 */
#include <stdint.h>
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#error "Generated code needs C11. Compile with -std=gnu11 or -std=c11."
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32) && !defined(_WIN64)
#include <unistd.h>
#include <xlang_io_cap.h>
#else
#include <io.h>
#include <sys/types.h>
#endif
#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/uio.h>
#endif
#if !defined(_WIN32) && !defined(_WIN64)
#include <poll.h>
#endif
#ifndef O_RDONLY
#define O_RDONLY 0
#endif
#ifndef O_WRONLY
#define O_WRONLY 1
#endif
#ifndef O_RDWR
#define O_RDWR 2
#endif
#if defined(__APPLE__)
#ifndef O_CREAT
#define O_CREAT 512
#endif
#ifndef O_TRUNC
#define O_TRUNC 1024
#endif
#ifndef O_APPEND
#define O_APPEND 8
#endif
#ifndef F_NOCACHE
#define F_NOCACHE 48
#endif
#else
#ifndef O_CREAT
#define O_CREAT 64
#endif
#ifndef O_TRUNC
#define O_TRUNC 512
#endif
#ifndef O_APPEND
#define O_APPEND 1024
#endif
#endif
#ifndef PROT_READ
#define PROT_READ 1
#endif
#ifndef PROT_WRITE
#define PROT_WRITE 2
#endif
#ifndef MAP_SHARED
#define MAP_SHARED 1
#endif
#ifndef MAP_PRIVATE
#define MAP_PRIVATE 2
#endif
#ifndef MAP_FAILED
#define MAP_FAILED ((int64_t)-1)
#endif
#ifndef S_IFMT
#define S_IFMT 61440u
#endif
#ifndef S_IFDIR
#define S_IFDIR 16384u
#endif
#ifndef S_IFREG
#define S_IFREG 32768u
#endif
#ifndef FS_IOV_BUF_MAX
#define FS_IOV_BUF_MAX 16
#endif
#ifndef DIRENT_D_NAME_OFF
#if defined(__APPLE__)
#define DIRENT_D_NAME_OFF ((size_t)21)
#else
#define DIRENT_D_NAME_OFF ((size_t)19)
#endif
#endif
#if !defined(_WIN32) && !defined(_WIN64)
#if defined(__APPLE__)
extern int *__error(void);
#else
extern int *__errno_location(void);
#endif
extern int32_t fcntl(int32_t fd, int32_t cmd, int32_t arg);
extern int32_t madvise(uint8_t *addr, size_t len, int32_t advice);
extern int32_t open(uint8_t *path, int32_t flags, int32_t mode);
static inline int32_t fs_libc_open(uint8_t *path, int32_t flags, int32_t mode) {
  return open(path, flags, mode);
}
#define fs_note_last_error_posix std_fs_posix_fs_note_last_error_posix
#endif
static inline ssize_t xlang_sys_read(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_read((int)fd, (void *)buf, count);
}
static inline ssize_t xlang_sys_write(int32_t fd, uint8_t *buf, size_t count) {
  return (ssize_t)xlang_io_write((int)fd, (const void *)buf, count);
}
#if !defined(_WIN32) && !defined(_WIN64)
static inline ssize_t xlang_sys_readv(int32_t fd, uint8_t *iov, int32_t iovcnt) {
  return readv((int)fd, (const struct iovec *)(const void *)iov, (int)iovcnt);
}
#endif
#if !defined(_WIN32) && !defined(_WIN64)
static inline ssize_t xlang_sys_writev(int32_t fd, uint8_t *iov, int32_t iovcnt) {
  return writev((int)fd, (const struct iovec *)(const void *)iov, (int)iovcnt);
}
#endif
#if !defined(_WIN32) && !defined(_WIN64)
static inline int32_t xlang_sys_poll(uint8_t *fds, int32_t nfds, int32_t timeout) {
  return (int32_t)poll((struct pollfd *)(void *)fds, (nfds_t)nfds, (int)timeout);
}
#endif
#if !defined(_WIN32) && !defined(_WIN64)
static inline ssize_t xlang_sys_pread(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {
  return pread((int)fd, (void *)buf, count, (off_t)offset);
}
#endif
#if !defined(_WIN32) && !defined(_WIN64)
static inline ssize_t xlang_sys_pwrite(int32_t fd, uint8_t *buf, size_t count, int64_t offset) {
  return pwrite((int)fd, (const void *)buf, count, (off_t)offset);
}
#endif
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
typedef float f32x4_t __attribute__((vector_size(16)));
typedef float f32x8_t __attribute__((vector_size(32)));
typedef float f32x16_t __attribute__((vector_size(64)));
#else
typedef struct { int32_t e[4]; } i32x4_t;
typedef struct { int32_t e[8]; } i32x8_t;
typedef struct { int32_t e[16]; } i32x16_t;
typedef struct { uint32_t e[4]; } u32x4_t;
typedef struct { uint32_t e[8]; } u32x8_t;
typedef struct { uint32_t e[16]; } u32x16_t;
typedef struct { float e[4]; } f32x4_t;
typedef struct { float e[8]; } f32x8_t;
typedef struct { float e[16]; } f32x16_t;
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
/* wave313 G.7: monofile dual WEAK polyfills → extern-only (n=30).
 * live STRONG = runtime/product .o (freestanding dual leave).
 * PLATFORM: SHARED freestanding dual leave. */
/* 仅补 co-emit 未定义的符号；勿桩 submit_read / submit_*_batch / submit_write（core 强定义）。 */
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
extern int32_t labi_diag_append(uint8_t * dst, int32_t cap, uint8_t * src);
extern void labi_diag_append_i32(uint8_t * dst, int32_t cap, int32_t v);
extern uint8_t * link_diag_code_for_kind(uint8_t * kind);
extern void link_diag_runtime_obj_resolve_fail(uint8_t * obj_name, uint8_t * hint);
extern void link_diag_runtime_source_missing(uint8_t * obj_name, uint8_t * source_path);
extern void link_diag_runtime_source_missing_under(uint8_t * obj_name, uint8_t * base_dir, uint8_t * suffix);
extern void link_diag_runtime_obj_missing(uint8_t * obj_name, uint8_t * out_o);
extern void link_diag_freestanding_missing(uint8_t * obj_name, uint8_t * symbol_name);
extern void link_diag_freestanding_unsupported(void);
extern void link_diag_ld_debug_push(uint8_t * rel, uint8_t * stage, uint8_t * path);
extern void link_diag_ld_debug_argv(uint8_t * label, uint8_t * argv);
extern void link_diag_tool_status(uint8_t * tool, int32_t status);
extern void link_diag_runtime_obj_build_status(uint8_t * obj_name, int32_t status);
extern void link_diag_errno(uint8_t * kind, uint8_t * op);
extern void link_diag_errno_path(uint8_t * kind, uint8_t * op, uint8_t * path);
extern void xlang_link_perror(uint8_t * msg);
extern int32_t xlang_waitpid_retry(int64_t pid, int32_t * status_out);
extern int32_t labi_diag_pure_count(void);
extern void diag_report_with_code(uint8_t * file, int32_t line, int32_t col, uint8_t * kind, uint8_t * code, uint8_t * msg, uint8_t * detail);
extern void link_diag_ld_debug_argv_impl(uint8_t * label, uint8_t * argv);
/* Cap residual mega always _impl (wave217); pure public thin defined below. */
extern uint8_t * link_diag_strerror_current_impl(void);
extern int32_t link_diag_wait_is_signaled_impl(int32_t status);
extern int32_t link_diag_wait_code_impl(int32_t status);
extern int32_t xlang_waitpid_retry_impl(int64_t pid, int32_t * status_out);
/* Cap residual mega always _impl (wave219); pure public thin defined below.
 * argv as uint8_t* matches product .x *u8 opaque char** width (export **u8 drops body). */
extern int32_t xlang_spawn_sync_impl(uint8_t * prog, uint8_t * argv);
/* Cap residual mega always _impl (wave220); pure public thin defined below. */
extern void invoke_cc_strip_out_x_impl(uint8_t * out_path);
/* Cap residual mega always _impl (wave222); pure public thin defined below. */
extern uint8_t * link_abi_getenv_impl(uint8_t * name);
/* Cap residual mega always _impl (wave224); pure public thin defined below. */
extern int32_t link_abi_system_impl(uint8_t * cmd);
/* Public pure thin (defined later in this TU; used by errno/tool/obj orch above). */
uint8_t * link_diag_strerror_current(void);
int32_t link_diag_wait_is_signaled(int32_t status);
int32_t link_diag_wait_code(int32_t status);
int32_t labi_diag_append(uint8_t * dst, int32_t cap, uint8_t * src) {
  int32_t i = 0;
  int32_t j = 0;
  if ((dst ==0)) {
    return 0;
  }
  if ((src ==0)) {
    while ((i < cap)) {
      if (((dst)[((size_t)(i))] ==0)) {
        return i;
      }
      (void)((i = (i + 1)));
    }
    return 0;
  }
  while ((i < cap)) {
    if (((dst)[((size_t)(i))] ==0)) {
      break;
    }
    (void)((i = (i + 1)));
  }
  if ((i >=cap)) {
    (void)(((dst)[((size_t)((cap - 1)))] = 0));
    return (cap - 1);
  }
  (void)((j = 0));
  while (((i + 1) < cap)) {
    uint8_t c = (src)[((size_t)(j))];
    if ((c ==0)) {
      break;
    }
    (void)(((dst)[((size_t)(i))] = c));
    (void)((i = (i + 1)));
    (void)((j = (j + 1)));
  }
  (void)(((dst)[((size_t)(i))] = 0));
  return i;
}
void labi_diag_append_i32(uint8_t * dst, int32_t cap, int32_t v) {
  uint8_t dig[16] = {};
  int32_t n = v;
  int32_t i = 0;
  int32_t j = 0;
  int32_t neg = 0;
  uint8_t a = 0;
  (void)(((dig)[0] = 0));
  if ((n ==0)) {
    (void)(((dig)[0] = 48));
    (void)(((dig)[1] = 0));
    (void)(labi_diag_append(dst, cap, &((dig)[0])));
    return;
  }
  if ((n < 0)) {
    (void)((neg = 1));
    (void)((n = (0 - n)));
  }
  while ((n > 0)) {
    if ((i >=15)) {
      break;
    }
    (void)(((dig)[i] = ((uint8_t)((48 + (n - ((n / 10) * 10)))))));
    (void)((n = (n / 10)));
    (void)((i = (i + 1)));
  }
  if ((neg !=0)) {
    if ((i < 15)) {
      (void)(((dig)[i] = 45));
      (void)((i = (i + 1)));
    }
  }
  (void)((j = 0));
  while ((j < (i / 2))) {
    (void)((a = (dig)[j]));
    (void)(((dig)[j] = (dig)[((i - 1) - j)]));
    (void)(((dig)[((i - 1) - j)] = a));
    (void)((j = (j + 1)));
  }
  (void)(((dig)[i] = 0));
  (void)(labi_diag_append(dst, cap, &((dig)[0])));
}
uint8_t * link_diag_code_for_kind(uint8_t * kind) {
  if ((kind ==0)) {
    uint8_t * p = ((uint8_t *)"\x50\x52\x43\x30\x30\x31");
    return p;
  }
  {
    uint8_t * be = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72");
    if ((strcmp(kind, be) ==0)) {
      uint8_t * p = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31");
      return p;
    }
    uint8_t * pe = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x20\x65\x72\x72\x6f\x72");
    if ((strcmp(kind, pe) ==0)) {
      uint8_t * p = ((uint8_t *)"\x50\x52\x43\x30\x30\x31");
      return p;
    }
  }
  return ((uint8_t *)(0));
}
void link_diag_runtime_obj_resolve_fail(uint8_t * obj_name, uint8_t * hint) {
  uint8_t * on = obj_name;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x63\x61\x6e\x6e\x6f\x74\x20\x72\x65\x73\x6f\x6c\x76\x65\x20\x63\x6f\x6d\x70\x69\x6c\x65\x72\x20\x64\x69\x72\x65\x63\x74\x6f\x72\x79\x20\x74\x6f\x20\x62\x75\x69\x6c\x64\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, on));
  if ((hint !=0)) {
    if (((hint)[((size_t)(0))] !=0)) {
      (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x28")));
      (void)(labi_diag_append(&((msg)[0]), 320, hint));
      (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x29")));
    }
  }
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_runtime_source_missing(uint8_t * obj_name, uint8_t * source_path) {
  uint8_t * on = obj_name;
  uint8_t * sp = source_path;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  if ((sp ==0)) {
    (void)((sp = ((uint8_t *)"\x3f")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, on));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x73\x6f\x75\x72\x63\x65\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x61\x74\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, sp));
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_runtime_source_missing_under(uint8_t * obj_name, uint8_t * base_dir, uint8_t * suffix) {
  uint8_t * on = obj_name;
  uint8_t * bd = base_dir;
  uint8_t * sf = suffix;
  uint8_t msg[384] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  if ((bd ==0)) {
    (void)((bd = ((uint8_t *)"\x3f")));
  }
  if ((sf ==0)) {
    (void)((sf = ((uint8_t *)"")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 384, on));
  (void)(labi_diag_append(&((msg)[0]), 384, ((uint8_t *)"\x20\x73\x6f\x75\x72\x63\x65\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x75\x6e\x64\x65\x72\x20")));
  (void)(labi_diag_append(&((msg)[0]), 384, bd));
  (void)(labi_diag_append(&((msg)[0]), 384, sf));
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_runtime_obj_missing(uint8_t * obj_name, uint8_t * out_o) {
  uint8_t * on = obj_name;
  uint8_t * oo = out_o;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  if ((oo ==0)) {
    (void)((oo = ((uint8_t *)"\x3f")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, on));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x6d\x69\x73\x73\x69\x6e\x67\x20\x61\x66\x74\x65\x72\x20\x63\x63\x20\x2d\x63\x20\x28\x65\x78\x70\x65\x63\x74\x65\x64\x20\x6e\x65\x61\x72\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, oo));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x29")));
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_freestanding_missing(uint8_t * obj_name, uint8_t * symbol_name) {
  uint8_t * on = obj_name;
  uint8_t * sn = symbol_name;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x66\x72\x65\x65\x73\x74\x61\x6e\x64\x69\x6e\x67\x20\x6c\x69\x6e\x6b\x20\x6d\x69\x73\x73\x69\x6e\x67\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, on));
  if ((sn !=0)) {
    if (((sn)[((size_t)(0))] !=0)) {
      (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x28\x75\x73\x65\x72\x20\x72\x65\x66\x65\x72\x65\x6e\x63\x65\x73\x20")));
      (void)(labi_diag_append(&((msg)[0]), 320, sn));
      (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x29")));
    }
  }
  (void)((kind = ((uint8_t *)"\x6c\x69\x6e\x6b\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_freestanding_unsupported(void) {
  uint8_t msg[192] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 192, ((uint8_t *)"\x2d\x66\x72\x65\x65\x73\x74\x61\x6e\x64\x69\x6e\x67\x20\x2f\x20\x53\x48\x55\x58\x5f\x46\x52\x45\x45\x53\x54\x41\x4e\x44\x49\x4e\x47\x20\x69\x73\x20\x6f\x6e\x6c\x79\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x66\x6f\x72\x20")));
  (void)(labi_diag_append(&((msg)[0]), 192, ((uint8_t *)"\x4c\x69\x6e\x75\x78\x20\x45\x4c\x46\x20\x78\x38\x36\x5f\x36\x34\x20\x28\x2d\x6f\x20\x70\x72\x6f\x67\x2c\x20\x6e\x6f\x74\x20\x2e\x6f\x2f\x2e\x6f\x62\x6a\x20\x6f\x6e\x20\x6d\x61\x63\x4f\x53\x2f\x43\x4f\x46\x46\x29")));
  (void)((kind = ((uint8_t *)"\x6c\x69\x6e\x6b\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_ld_debug_push(uint8_t * rel, uint8_t * stage, uint8_t * path) {
  uint8_t * r = rel;
  uint8_t * st = stage;
  uint8_t * p = path;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  if ((r ==0)) {
    (void)((r = ((uint8_t *)"\x28\x6e\x75\x6c\x6c\x29")));
  }
  if ((st ==0)) {
    (void)((st = ((uint8_t *)"\x70\x61\x74\x68")));
  }
  if ((p ==0)) {
    (void)((p = ((uint8_t *)"\x28\x6e\x75\x6c\x6c\x29")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x6c\x64\x20\x64\x65\x62\x75\x67\x3a\x20\x70\x75\x73\x68\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, r));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, st));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x3d")));
  (void)(labi_diag_append(&((msg)[0]), 320, p));
  (void)((kind = ((uint8_t *)"\x6e\x6f\x74\x65")));
  (void)(diag_report_with_code(0, 0, 0, kind, 0, &((msg)[0]), 0));
}
void link_diag_ld_debug_argv(uint8_t * label, uint8_t * argv) {
  (void)(link_diag_ld_debug_argv_impl(label, argv));
}
void link_diag_tool_status(uint8_t * tool, int32_t status) {
  uint8_t * t = tool;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  int32_t sig = 0;
  int32_t c = 0;
  if ((t ==0)) {
    (void)((t = ((uint8_t *)"\x74\x6f\x6f\x6c")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, t));
  (void)((sig = link_diag_wait_is_signaled(status)));
  (void)((c = link_diag_wait_code(status)));
  if ((sig !=0)) {
    (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x73\x69\x67\x6e\x61\x6c\x20")));
  } else {
    (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x65\x78\x69\x74\x20")));
  }
  (void)(labi_diag_append_i32(&((msg)[0]), 320, c));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x29")));
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_runtime_obj_build_status(uint8_t * obj_name, int32_t status) {
  uint8_t * on = obj_name;
  uint8_t msg[320] = {};
  uint8_t * kind = 0;
  uint8_t * code = 0;
  int32_t sig = 0;
  int32_t c = 0;
  if ((on ==0)) {
    (void)((on = ((uint8_t *)"\x72\x75\x6e\x74\x69\x6d\x65\x20\x6f\x62\x6a\x65\x63\x74")));
  }
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x62\x75\x69\x6c\x64\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, on));
  (void)((sig = link_diag_wait_is_signaled(status)));
  (void)((c = link_diag_wait_code(status)));
  if ((sig !=0)) {
    (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x28\x73\x69\x67\x6e\x61\x6c\x20")));
  } else {
    (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x28\x65\x78\x69\x74\x20")));
  }
  (void)(labi_diag_append_i32(&((msg)[0]), 320, c));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x29")));
  (void)((kind = ((uint8_t *)"\x62\x75\x69\x6c\x64\x20\x65\x72\x72\x6f\x72")));
  (void)((code = ((uint8_t *)"\x42\x4c\x44\x30\x30\x31")));
  (void)(diag_report_with_code(0, 0, 0, kind, code, &((msg)[0]), 0));
}
void link_diag_errno(uint8_t * kind, uint8_t * op) {
  uint8_t * k = kind;
  uint8_t * o = op;
  uint8_t * err = 0;
  uint8_t * code = 0;
  uint8_t msg[320] = {};
  if ((k ==0)) {
    (void)((k = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x20\x65\x72\x72\x6f\x72")));
  }
  if ((o ==0)) {
    (void)((o = ((uint8_t *)"\x73\x79\x73\x74\x65\x6d\x20\x63\x61\x6c\x6c")));
  } else {
    if (((o)[0] ==0)) {
      (void)((o = ((uint8_t *)"\x73\x79\x73\x74\x65\x6d\x20\x63\x61\x6c\x6c")));
    }
  }
  (void)((err = link_diag_strerror_current()));
  if ((err ==0)) {
    (void)((err = ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x65\x72\x72\x6f\x72")));
  }
  (void)((code = link_diag_code_for_kind(k)));
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 320, o));
  (void)(labi_diag_append(&((msg)[0]), 320, ((uint8_t *)"\x20\x66\x61\x69\x6c\x65\x64\x3a\x20")));
  (void)(labi_diag_append(&((msg)[0]), 320, err));
  (void)(diag_report_with_code(0, 0, 0, k, code, &((msg)[0]), 0));
}
void link_diag_errno_path(uint8_t * kind, uint8_t * op, uint8_t * path) {
  uint8_t * k = kind;
  uint8_t * o = op;
  uint8_t * p = path;
  uint8_t * err = 0;
  uint8_t * code = 0;
  uint8_t msg[384] = {};
  if ((p ==0)) {
    (void)(link_diag_errno(k, o));
    return;
  }
  if (((p)[0] ==0)) {
    (void)(link_diag_errno(k, o));
    return;
  }
  if ((k ==0)) {
    (void)((k = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x20\x65\x72\x72\x6f\x72")));
  }
  if ((o ==0)) {
    (void)((o = ((uint8_t *)"\x73\x79\x73\x74\x65\x6d\x20\x63\x61\x6c\x6c")));
  } else {
    if (((o)[0] ==0)) {
      (void)((o = ((uint8_t *)"\x73\x79\x73\x74\x65\x6d\x20\x63\x61\x6c\x6c")));
    }
  }
  (void)((err = link_diag_strerror_current()));
  if ((err ==0)) {
    (void)((err = ((uint8_t *)"\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x65\x72\x72\x6f\x72")));
  }
  (void)((code = link_diag_code_for_kind(k)));
  (void)(((msg)[0] = 0));
  (void)(labi_diag_append(&((msg)[0]), 384, o));
  (void)(labi_diag_append(&((msg)[0]), 384, ((uint8_t *)"\x20\x66\x61\x69\x6c\x65\x64\x20\x66\x6f\x72\x20\x27")));
  (void)(labi_diag_append(&((msg)[0]), 384, p));
  (void)(labi_diag_append(&((msg)[0]), 384, ((uint8_t *)"\x27\x3a\x20")));
  (void)(labi_diag_append(&((msg)[0]), 384, err));
  (void)(diag_report_with_code(0, 0, 0, k, code, &((msg)[0]), 0));
}
void xlang_link_perror(uint8_t * msg) {
  uint8_t * pe = ((uint8_t *)"\x70\x72\x6f\x63\x65\x73\x73\x20\x65\x72\x72\x6f\x72");
  uint8_t * sc = ((uint8_t *)"\x73\x79\x73\x74\x65\x6d\x20\x63\x61\x6c\x6c");
  uint8_t * base = msg;
  int32_t start = 0;
  int32_t n = 0;
  int32_t i = 0;
  int32_t lparen = -1;
  int32_t rparen = -1;
  int32_t op_end = 0;
  int32_t op_len = 0;
  int32_t path_len = 0;
  int32_t j = 0;
  uint8_t op_buf[128] = {};
  uint8_t path_buf[160] = {};
  uint8_t * text = 0;
  if ((base ==0)) {
    (void)(link_diag_errno(pe, sc));
    return;
  }
  if (((base)[0] ==0)) {
    (void)(link_diag_errno(pe, sc));
    return;
  }
  if (((base)[0] ==115)) {
    if (((base)[1] ==104)) {
      if (((base)[2] ==117)) {
        if (((base)[3] ==120)) {
          if (((base)[4] ==58)) {
            if (((base)[5] ==32)) {
              (void)((start = 6));
            }
          }
        }
      }
    }
  }
  (void)((n = start));
  while (((base)[n] !=0)) {
    (void)((n = (n + 1)));
  }
  (void)((i = start));
  while ((i < n)) {
    if (((base)[i] ==40)) {
      (void)((lparen = i));
    }
    if (((base)[i] ==41)) {
      (void)((rparen = i));
    }
    (void)((i = (i + 1)));
  }
  if ((((lparen >=start) && (rparen > lparen)) && ((rparen + 1) ==n))) {
    (void)((op_end = lparen));
    while (((op_end > start) && ((base)[(op_end - 1)] ==32))) {
      (void)((op_end = (op_end - 1)));
    }
    (void)((op_len = (op_end - start)));
    if ((op_len >=128)) {
      (void)((op_len = 127));
    }
    (void)((path_len = ((rparen - lparen) - 1)));
    if ((path_len >=160)) {
      (void)((path_len = 159));
    }
    (void)((j = 0));
    while ((j < op_len)) {
      (void)(((op_buf)[((size_t)(j))] = (base)[((size_t)((start + j)))]));
      (void)((j = (j + 1)));
    }
    (void)(((op_buf)[((size_t)(op_len))] = 0));
    (void)((j = 0));
    while ((j < path_len)) {
      (void)(((path_buf)[((size_t)(j))] = (base)[((size_t)(((lparen + 1) + j)))]));
      (void)((j = (j + 1)));
    }
    (void)(((path_buf)[((size_t)(path_len))] = 0));
    (void)(link_diag_errno_path(pe, &((op_buf)[0]), &((path_buf)[0])));
    return;
  }
  (void)((text = &((base)[start])));
  (void)(link_diag_errno(pe, text));
}
/* wave217: strerror_current + wait decode pure thin (surface pin ≡ .x). */
uint8_t * link_diag_strerror_current(void) {
  {
    return link_diag_strerror_current_impl();
  }
  return 0;
}
int32_t link_diag_wait_is_signaled(int32_t status) {
  {
    return link_diag_wait_is_signaled_impl(status);
  }
  return 0;
}
int32_t link_diag_wait_code(int32_t status) {
  {
    return link_diag_wait_code_impl(status);
  }
  return (0 - 1);
}
/* wave216: xlang_waitpid_retry pure thin (surface pin ≡ .x). */
int32_t xlang_waitpid_retry(int64_t pid, int32_t * status_out) {
  {
    return xlang_waitpid_retry_impl(pid, status_out);
  }
  return (0 - 1);
}
/* wave219: xlang_spawn_sync pure thin (surface pin ≡ .x; null/empty gates + Cap residual). */
int32_t xlang_spawn_sync(uint8_t * prog, uint8_t * argv) {
  if ((prog == 0)) {
    return (0 - 1);
  }
  if (((prog)[0] == 0)) {
    return (0 - 1);
  }
  if ((argv == 0)) {
    return (0 - 1);
  }
  {
    return xlang_spawn_sync_impl(prog, argv);
  }
  return (0 - 1);
}
/* wave220: invoke_cc_strip_out_x pure thin (surface pin ≡ .x; null/empty gates + Cap residual). */
void invoke_cc_strip_out_x(uint8_t * out_path) {
  if ((out_path == 0)) {
    return;
  }
  if (((out_path)[0] == 0)) {
    return;
  }
  {
    invoke_cc_strip_out_x_impl(out_path);
  }
}
/* wave222: link_abi_getenv pure thin (surface pin ≡ .x; null/empty gates + Cap residual). */
uint8_t * link_abi_getenv(uint8_t * name) {
  if ((name ==((uint8_t *)(0)))) {
    return ((uint8_t *)(0));
  }
  if (((name)[0] ==0)) {
    return ((uint8_t *)(0));
  }
  {
    return link_abi_getenv_impl(name);
  }
  return ((uint8_t *)(0));
}
/* wave224: link_abi_system pure thin (surface pin ≡ .x; null/empty gates + Cap residual). */
int32_t link_abi_system(uint8_t * cmd) {
  if ((cmd ==((uint8_t *)(0)))) {
    return (0 - 1);
  }
  if (((cmd)[0] ==0)) {
    return (0 - 1);
  }
  {
    return link_abi_system_impl(cmd);
  }
  return (0 - 1);
}
int32_t labi_diag_pure_count(void) {
  return 9;
}
