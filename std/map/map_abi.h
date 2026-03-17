/**
 * std/map/map_abi.h — std.map / std.heap 与 codegen 生成 C 的 ABI 头文件
 *
 * 供编译器在生成 .c 时通过 #include "std/map/map_abi.h" 引入。
 * map_i32_i32_find_c 实现在 std/heap/heap.c；map_empty_size 由 std.map 生成，宏转发到 std_map_map_empty_size。
 */
#ifndef STD_MAP_MAP_ABI_H
#define STD_MAP_MAP_ABI_H

#include <stdint.h>

extern int32_t map_i32_i32_find_c(const int32_t *keys, const uint8_t *occupied, int32_t cap, int32_t key);
extern int32_t std_map_map_empty_size(void);
#define map_empty_size(_a, _b) std_map_map_empty_size()

#endif /* STD_MAP_MAP_ABI_H */
