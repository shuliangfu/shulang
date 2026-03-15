# std.map — 映射/字典

与 **Zig** std.AutoHashMap、**Rust** HashMap、**Go** map 对标。

## 类型

- **Map_i32_i32**：键值均为 i32，堆分配 keys/vals/occupied，须在不用时 `map_i32_i32_deinit`。

## API

| 函数 | 说明 |
|------|------|
| `map_i32_i32_new()` | 新建空 map |
| `map_i32_i32_with_capacity(m, capacity)` | 预分配槽位；失败返回 -1 |
| `map_i32_i32_insert(m, key, value)` | 插入/覆盖；失败返回 -1 |
| `map_i32_i32_get(m, key, default_val)` | 取值，不存在返回 default_val |
| `map_i32_i32_contains(m, key)` | 是否包含 key |
| `map_i32_i32_remove(m, key)` | 移除 key；存在返回 1，否则 0 |
| `map_i32_i32_len(m)` / `map_i32_i32_is_empty(m)` | 条目数 / 是否为空 |
| `map_i32_i32_clear(m)` / `map_i32_i32_reserve(m, new_cap)` | 清空 / 扩容 |
| `map_i32_i32_deinit(m)` | 释放堆，调用后不可再用 |

## 实现

- 线性探测哈希表；**负载因子 > 0.75** 时 2 倍扩容（减少 rehash 频率）。

## 性能（已压榨）

- **find 走 C 快路径**：`map_i32_i32_find_c`（在 heap.o）内线性探测，get/contains/remove/insert 均复用，避免 .su 层循环。
- **reserve_one**：字面量 8 与 3/4 负载因子，避免阈值函数调用。
- **with_capacity**：occupied 清零用 **4 字节展开** 循环。
- **热路径**：`map_i32_i32_len_ptr` 避免按值传 Map 结构体。

## 依赖

- `import std.heap`；链接时需 `std/heap/heap.o`（含 map_i32_i32_find_c）。
