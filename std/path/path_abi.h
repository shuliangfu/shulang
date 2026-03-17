/**
 * std/path/path_abi.h — std.path 与 codegen 生成 C 的 ABI 头文件
 *
 * 供编译器在生成 .c 时通过 #include "std/path/path_abi.h" 引入。
 * 生成代码可能以 path_empty_len(0, 0) 形式调用，此处宏转发到 std_path_path_empty_len。
 */
#ifndef STD_PATH_PATH_ABI_H
#define STD_PATH_PATH_ABI_H

#include <stdint.h>

extern int32_t std_path_path_empty_len(void);
#define path_empty_len(_a, _b) std_path_path_empty_len()

#endif /* STD_PATH_PATH_ABI_H */
