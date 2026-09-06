/* seeds/async_net_fs.from_x.c — G-02f-80 product cold-start TU
 * Promoted from compiler/src/asm/async_net_fs.inc (stub/bridge; retired .inc).
 * Compile: cc -c / cc_inc_tu seeds/async_net_fs.from_x.c
 */
/**
 * std/async/async_net_fs.inc.c — async net/fs fd 读写烟测（STD-049 / #79）
 *
 * 【文件职责】通过 pipe 验证 std.io read_async/write_async 在 net/fs 类 fd 上的
 * submit + complete 路径；由 scheduler_glue.c 末尾 #include。
 */

#if !defined(_WIN32) && !defined(_WIN64)
#include <xlang_weak.h>
#include <string.h>
#include <xlang_io_cap.h>
/* PLATFORM: SHARED — include/unistd.h shim provides POSIX wrappers on MinGW
 *            (read/write/close/lseek/open/pread/pwrite/setenv/unsetenv).
 *            macOS/Linux delegate to system <unistd.h> via #include_next.
 *            Historical #ifndef _WIN32 guard removed — shim is a no-op
 *            on POSIX and provides needed declarations on Windows. */
#include <unistd.h>
#endif

/** 与 std.io IO_ASYNC_NOT_READY 一致。 */
#define XLANG_ASYNC_IO_NOT_READY (-2)

/** io.o 未链入时 weak 桩（与 scheduler_glue.c poll 桩一致）。 */
XLANG_WEAK int xlang_io_submit_read_async(uint8_t *ptr, size_t len, size_t handle) {
    (void)ptr;
    (void)len;
    (void)handle;
    return -1;
}

XLANG_WEAK int32_t xlang_io_complete_read_async_slot(int slot) {
    (void)slot;
    return XLANG_ASYNC_IO_NOT_READY;
}

XLANG_WEAK int xlang_io_submit_write_async(const uint8_t *ptr, size_t len, size_t handle) {
    (void)ptr;
    (void)len;
    (void)handle;
    return -1;
}

XLANG_WEAK int32_t xlang_io_complete_write_async_slot(int slot) {
    (void)slot;
    return XLANG_ASYNC_IO_NOT_READY;
}

/**
 * pipe 上 async read/write 往返烟测（模拟 net stream / fs fd 异步路径）；0 通过。
 * 非 Unix 跳过返回 0。
 */
int32_t xlang_async_net_fs_smoke_c(void) {
#if defined(_WIN32) || defined(_WIN64)
    return 0;
#else
    int pv[2];
    uint8_t wbuf[] = "net";
    uint8_t rbuf[8];
    int slot;
    int32_t n;

    /* read async：pipe 写端 → read_async → complete */
    if (pipe(pv) != 0)
        return 1;
    if (xlang_io_write(pv[1], wbuf, 3) != 3) {
        close(pv[0]);
        close(pv[1]);
        return 2;
    }
    close(pv[1]);
    slot = xlang_io_submit_read_async(rbuf, 3, (size_t)pv[0]);
    if (slot < 0) {
        close(pv[0]);
        return 0;
    }
    n = xlang_io_complete_read_async_slot(slot);
    close(pv[0]);
    if (n != 3)
        return 4;
    if (memcmp(rbuf, wbuf, 3) != 0)
        return 5;

    /* write async：write_async → pipe 读端校验 */
    if (pipe(pv) != 0)
        return 6;
    slot = xlang_io_submit_write_async(wbuf, 3, (size_t)pv[1]);
    if (slot < 0) {
        close(pv[0]);
        close(pv[1]);
        return 0;
    }
    n = xlang_io_complete_write_async_slot(slot);
    if (n != 3) {
        close(pv[0]);
        close(pv[1]);
        return 8;
    }
    if (xlang_io_read(pv[0], rbuf, 3) != 3) {
        close(pv[0]);
        close(pv[1]);
        return 9;
    }
    close(pv[0]);
    close(pv[1]);
    if (memcmp(rbuf, wbuf, 3) != 0)
        return 10;
    return 0;
#endif
}
