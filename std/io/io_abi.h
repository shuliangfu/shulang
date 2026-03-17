/**
 * std/io/io_abi.h — std.io 与 codegen 生成 C 的 ABI 头文件
 *
 * 供编译器在生成 .c 时通过 #include "std/io/io_abi.h" 引入，
 * 不再在 runtime.c 内联大段 extern/宏字符串（从源头去补丁）。
 * 与 std/io/io.c、std/io/core.su 等产出的符号一致。
 */
#ifndef STD_IO_IO_ABI_H
#define STD_IO_IO_ABI_H

#include <stddef.h>
#include <stdint.h>

typedef struct { uint8_t *ptr; size_t len; size_t handle; } shu_batch_buf_t;

extern int io_register_buffer(uint8_t *ptr, size_t len);
extern int io_register_buffers_4(uint8_t *p0, size_t l0, uint8_t *p1, size_t l1, uint8_t *p2, size_t l2, uint8_t *p3, size_t l3, unsigned nr);
extern int io_register_buffers_buf(const shu_batch_buf_t *bufs, int nr);
static inline int io_register_buffers_buf_i32(int32_t bufs, int nr) { return io_register_buffers_buf((const shu_batch_buf_t *)(uintptr_t)bufs, nr); }
#define io_register_buffers_buf io_register_buffers_buf_i32
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

/* std.io.core 生成无前缀符号 shu_io_*，前向声明与 codegen 产出一致（指针/size_t 避免 64 位截断）。 */
extern int32_t shu_io_register(uint8_t *ptr, size_t len, size_t handle);
extern int32_t shu_io_submit_read(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
extern int32_t shu_io_submit_write(uint8_t *ptr, size_t len, size_t handle, uint32_t timeout_m);
extern int32_t shu_io_read_fixed(int32_t fd, int32_t buf_index, int32_t offset, int32_t len, int32_t timeout_m);
extern int32_t shu_io_write_fixed(int32_t fd, int32_t buf_index, int32_t offset, int32_t len, int32_t timeout_m);
extern int32_t shu_io_read_ptr_len(void);

/* Buffer ABI 与 std.io.driver 一致：ptr/len/handle 各 8 字节。 */
typedef struct { void *ptr; size_t len; size_t handle; } shu_buffer_abi_t;
/* 单参 buf 时由包装展开为 3 参，避免 parser 单参占位与 3 参定义冲突。 */
static inline int32_t shu_io_register_buf(int32_t buf) {
  const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf;
  return shu_io_register((uint8_t *)b->ptr, b->len, b->handle);
}
static inline int32_t shu_io_submit_read_buf(int32_t buf, int32_t timeout_m) {
  const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf;
  return (shu_io_submit_read)((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m);
}
static inline int32_t shu_io_submit_write_buf(int32_t buf, int32_t timeout_m) {
  const shu_buffer_abi_t *b = (const shu_buffer_abi_t *)(uintptr_t)buf;
  return (shu_io_submit_write)((uint8_t *)b->ptr, b->len, b->handle, (uint32_t)timeout_m);
}
#define shu_io_register(buf) shu_io_register_buf(buf)
#define shu_io_submit_read(buf, timeout_m) shu_io_submit_read_buf(buf, timeout_m)
#define shu_io_submit_write(buf, timeout_m) shu_io_submit_write_buf(buf, timeout_m)

/* driver 符号：std.io 调用时可能传 struct 值或指针；提供与 codegen 一致的 struct 名 + 按值/按指针两种包装。 */
struct std_io_driver_Buffer { void *ptr; size_t len; size_t handle; };
static inline int32_t std_io_driver_submit_write_ptr(const shu_buffer_abi_t *b, uint32_t timeout_m) {
  return (shu_io_submit_write)((uint8_t *)b->ptr, b->len, b->handle, timeout_m);
}
static inline int32_t std_io_driver_submit_write(struct std_io_driver_Buffer b, uint32_t timeout_m) {
  return (shu_io_submit_write)((uint8_t *)b.ptr, b.len, b.handle, timeout_m);
}
static inline int32_t std_io_driver_submit_read(struct std_io_driver_Buffer b, uint32_t timeout_m) {
  return (shu_io_submit_read)((uint8_t *)b.ptr, b.len, b.handle, timeout_m);
}
#define std_io_driver_driver_read_ptr_len shu_io_read_ptr_len
#define std_io_driver_driver_read_ptr shu_io_read_ptr
#define std_io_driver_submit_register_fixed_buffers_buf io_register_buffers_buf_i32
#define driver_read_ptr_len std_io_driver_driver_read_ptr_len
#define driver_read_ptr std_io_driver_driver_read_ptr
#define submit_register_fixed_buffers_buf std_io_driver_submit_register_fixed_buffers_buf

/* core 生成无前缀 shu_io_* 时，io.o 内调用可直接解析。 */
#define std_io_core_shu_io_register shu_io_register
#define std_io_core_shu_io_register_buffers shu_io_register_buffers
#define std_io_core_shu_io_unregister_buffers shu_io_unregister_buffers
#define std_io_core_shu_io_submit_read shu_io_submit_read
#define std_io_core_shu_io_read_ptr shu_io_read_ptr
#define std_io_core_shu_io_read_ptr_len shu_io_read_ptr_len
#define std_io_core_shu_io_submit_write shu_io_submit_write
#define std_io_core_shu_io_submit_read_batch shu_io_submit_read_batch
#define std_io_core_shu_io_submit_write_batch shu_io_submit_write_batch

#endif /* STD_IO_IO_ABI_H */
