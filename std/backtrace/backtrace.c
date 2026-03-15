/**
 * std/backtrace/backtrace.c — 调用栈捕获（对标 Rust std::backtrace）
 *
 * 【文件职责】
 * capture：将当前调用栈的帧指针/返回地址写入 buf（每帧 sizeof(void*) 字节），返回帧数。
 * symbolicate：平台相关，暂为 stub；完整实现可对接 backtrace_symbols/dladdr 等。
 *
 * 【所属模块/组件】
 * 标准库 std.backtrace；与 std/backtrace/mod.su 同属一模块。平台差异大，先提供 capture。
 */

#include <stdint.h>
#include <stddef.h>

#if defined(__linux__) || defined(__APPLE__)
#include <execinfo.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/** 将当前调用栈捕获到 buf；buf 按帧存储，每帧 sizeof(void*) 字节（通常 8）。
 * 返回写入的帧数（≤ max_frames）；失败或不支持平台返回 0。
 */
int32_t backtrace_capture_c(uint8_t *buf, int32_t max_frames) {
    if (!buf || max_frames <= 0) return 0;
#if defined(__linux__) || defined(__APPLE__)
    {
        void *arr[256];
        int n = backtrace(arr, max_frames > 256 ? 256 : (int)max_frames);
        if (n <= 0) return 0;
        size_t ptr_size = sizeof(void *);
        for (int i = 0; i < n; i++) {
            void *p = arr[i];
            uint8_t *dst = buf + (size_t)i * ptr_size;
            const uint8_t *src = (const uint8_t *)&p;
            for (size_t k = 0; k < ptr_size; k++) dst[k] = src[k];
        }
        return (int32_t)n;
    }
#elif defined(_WIN32) || defined(_WIN64)
    {
        void *arr[256];
        uint32_t n = CaptureStackBackTrace(0, (uint32_t)(max_frames > 256 ? 256 : max_frames), arr, NULL);
        if (n == 0) return 0;
        size_t ptr_size = sizeof(void *);
        for (uint32_t i = 0; i < n; i++) {
            void *p = arr[i];
            uint8_t *dst = buf + (size_t)i * ptr_size;
            const uint8_t *src = (const uint8_t *)&p;
            for (size_t k = 0; k < ptr_size; k++) dst[k] = src[k];
        }
        return (int32_t)n;
    }
#else
    (void)buf;
    (void)max_frames;
    return 0;
#endif
}

/** 将 capture 得到的 buf 符号化；平台相关。当前为 stub，返回 0。 */
int32_t backtrace_symbolicate_c(const uint8_t *buf, int32_t len, uint8_t *out_ptrs, uint8_t *out_names, int32_t max) {
    (void)buf;
    (void)len;
    (void)out_ptrs;
    (void)out_names;
    (void)max;
    return 0;
}
