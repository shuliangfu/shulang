/**
 * ABI/布局 断言测试（与 analysis/ABI与布局.md、内存契约.md 一致）
 * 编译并运行：cc -o layout_abi layout_abi.c && ./layout_abi
 * 若断言失败则编译或运行失败。
 */
#include <stddef.h>
#include <stdint.h>

/* 切片 []T 的 C 侧布局：与 codegen 生成的 struct shulang_slice_<elem> 一致 */
struct shulang_slice_u8 {
    uint8_t *data;
    size_t length;
};

/* packed 结构体：无填充，1+4=5 字节（与 tests/memory-contract/packed_struct.su 中 Header 一致） */
struct Header_packed {
    uint8_t tag;
    uint32_t len;
} __attribute__((packed));

/* std.mem.Buffer ABI：ptr + len + handle = 8+8+8 = 24 字节（高并发IO 第八节三项约定之一） */
struct std_mem_Buffer {
    uint8_t *ptr;
    size_t len;
    size_t handle;
};

int main(void) {
    /* 切片：64 位下 8+8=16 字节，data 偏移 0，length 偏移 8 */
    if (sizeof(size_t) == 8) {
        if (sizeof(struct shulang_slice_u8) != 16) return 1;
        if (offsetof(struct shulang_slice_u8, data) != 0) return 2;
        if (offsetof(struct shulang_slice_u8, length) != 8) return 3;
    }
    /* packed Header：1+4=5 */
    if (sizeof(struct Header_packed) != 5) return 4;
    if (offsetof(struct Header_packed, tag) != 0) return 5;
    if (offsetof(struct Header_packed, len) != 1) return 6;
    /* Buffer：64 位下 24 字节，ptr 0、len 8、handle 16 */
    if (sizeof(size_t) == 8) {
        if (sizeof(struct std_mem_Buffer) != 24) return 7;
        if (offsetof(struct std_mem_Buffer, ptr) != 0) return 8;
        if (offsetof(struct std_mem_Buffer, len) != 8) return 9;
        if (offsetof(struct std_mem_Buffer, handle) != 16) return 10;
    }
    return 0;
}
