# std.set — 集合（HashSet）

**路径**：`std/set/`（仅 mod.su，无 .c）  
**依赖**：std.heap（复用 map_i32_i32_find_c）。对标 Rust HashSet、Zig AutoSet。

| API | 说明 |
|-----|------|
| `set_i32_new()` | 新建空集合 |
| `set_i32_with_capacity(s, cap)` | 预分配槽位；失败 -1 |
| `set_i32_insert(s, key)` | 插入；失败 -1 |
| `set_i32_remove(s, key)` | 移除；存在返回 1 |
| `set_i32_contains(s, key)` | 是否包含；1/0 |
| `set_i32_len(s)` / `set_i32_is_empty(s)` | 个数 / 是否为空 |
| `set_i32_clear(s)` / `set_i32_reserve(s, new_cap)` | 清空 / 扩容 |
| `set_i32_deinit(s)` | 释放，调用后不可再用 |
