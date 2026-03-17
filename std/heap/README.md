# std.heap — 堆分配

与 **Zig** Allocator、**Rust** alloc::alloc、**Go** 运行时底层一致：显式 alloc/free/realloc。

## API

| 函数 | 说明 |
|------|------|
| `alloc(size: usize)` | 分配 size 字节，未初始化；失败返回 null |
| `free(ptr: *u8)` | 释放 ptr；ptr 可为 null |
| `realloc(ptr: *u8, new_size: usize)` | 调整大小；new_size==0 等价 free |
| `alloc_zeroed(size: usize)` | 分配并清零（calloc 语义） |
| `alloc_i32(count: i32)` / `realloc_i32` / `free_i32` | 按 i32 数组分配，供 std.vec 等使用 |
| `alloc_u8(count: i32)` / `realloc_u8` / `free_u8` | 按 u8 数组分配，供 std.vec Vec_u8 等使用 |

## 依赖

- 实现：`std/heap/heap.c`，链接时需 `std/heap/heap.o`（shu -o exe 时自动链入）。

## 约定

- 分配失败返回 null；调用方须检查。
- free(null) 无操作；realloc(ptr, 0) 等价 free 并返回 null。

## 性能

- 所有接口为 libc 薄封装，无额外分支；链接时可用 **-flto** 内联。
- **copy_i32_at / copy_u8_at**：块拷贝走 memcpy，供 std.vec append_slice/from_slice 快路径（≥8 元素）。
