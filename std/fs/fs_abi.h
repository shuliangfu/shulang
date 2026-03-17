/**
 * std/fs/fs_abi.h — std.fs 与 codegen 生成 C 的 ABI 头文件
 *
 * 供编译器在生成 .c 时通过 #include "std/fs/fs_abi.h" 引入，
 * 声明 fs.c 提供的 _c 符号，供 std/fs/mod.su 生成代码调用。
 */
#ifndef STD_FS_FS_ABI_H
#define STD_FS_FS_ABI_H

#include <stddef.h>
#include <stdint.h>

typedef struct { uint8_t *ptr; size_t len; size_t handle; } fs_iovec_buf_t;

extern uint64_t fs_direct_align_c(void);
extern int32_t fs_fadvise_sequential_c(int32_t fd);
extern int32_t fs_fadvise_willneed_c(int32_t fd, int64_t offset, size_t len);
extern int64_t fs_copy_file_range_c(int32_t fd_in, int32_t fd_out, size_t len);
extern int64_t fs_sendfile_c(int32_t out_fd, int32_t in_fd, size_t count);
extern int32_t fs_sync_range_c(int32_t fd, int64_t offset, size_t len);
extern int32_t fs_sync_c(int32_t fd);
extern int32_t fs_fallocate_c(int32_t fd, int64_t offset, int64_t len);
extern int32_t fs_last_error_c(void);
extern int64_t fs_readv_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);
extern int64_t fs_writev_buf_c(int32_t fd, const fs_iovec_buf_t *bufs, int n);

#endif /* STD_FS_FS_ABI_H */
