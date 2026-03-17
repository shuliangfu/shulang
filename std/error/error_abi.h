/**
 * std/error/error_abi.h — std.error 与 codegen 生成 C 的 ABI 头文件
 *
 * 供编译器在生成 .c 时通过 #include "std/error/error_abi.h" 引入。
 * 生成代码可能以 error_ok(0, 0) 形式调用，此处宏转发到 std_error_error_ok。
 */
#ifndef STD_ERROR_ERROR_ABI_H
#define STD_ERROR_ERROR_ABI_H

#include <stdint.h>

extern int32_t std_error_error_ok(void);
#define error_ok(_a, _b) std_error_error_ok()

#endif /* STD_ERROR_ERROR_ABI_H */
