# std.vec — 动态数组

与 **Zig** std.ArrayList、**Rust** Vec、**Go** slice+append 对标。

## 类型

- **Vec_i32**：`{ ptr: *i32, len: i32, cap: i32 }`，堆分配，须在不用时 `vec_i32_deinit`。
- **Vec_u8**：`{ ptr: *u8, len: i32, cap: i32 }`，同上。

## Vec_i32 API

| 函数 | 说明 |
|------|------|
| `vec_i32_new()` | 新建空 vec |
| `vec_i32_with_capacity(v, capacity)` | 预分配容量；失败返回 -1 |
| `vec_i32_push(v, x)` | 追加元素；失败返回 -1 |
| `vec_i32_pop(v)` | 移除并返回最后元素（空 vec 未定义） |
| `vec_i32_len(v)` / `vec_i32_capacity(v)` | 长度 / 容量 |
| `vec_i32_get(v, i)` / `vec_i32_set(v, i, x)` | 读/写第 i 个元素 |
| `vec_i32_is_empty(v)` | 是否为空 |
| `vec_i32_clear(v)` / `vec_i32_truncate(v, new_len)` | 清空 / 截断 |
| `vec_i32_reserve(v, new_cap)` | 确保容量 |
| `vec_i32_append_slice(v, ptr, n)` | 追加切片 |
| `vec_i32_from_slice(ptr, n)` | 从切片构造（失败时 len=-1） |
| `vec_i32_ptr(v)` | 零拷贝：内部缓冲首指针 |
| `vec_i32_deinit(v)` | 释放堆，调用后不可再用 |

Vec_u8 接口对称：`vec_u8_*`。

## 性能（已压榨）

- **默认容量 8**：减少首次几次 push 的 realloc。
- **append_slice / from_slice**：**≥8 元素走 C memcpy**（heap.copy_i32_at / copy_u8_at）；&lt;8 用 4 元素展开循环。
- **reserve_one**：热路径先判 `len < cap`，字面量 8 避免调用 default_capacity()。
- **热路径 _ptr**：`vec_i32_len_ptr`、`vec_u8_len_ptr` 避免按值传 Vec 结构体。

## 依赖

- `import std.heap`；链接时需 `std/heap/heap.o`。
