# std.queue — 双端队列（VecDeque）

**路径**：`std/queue/`（仅 mod.su）  
**依赖**：std.heap。对标 Rust VecDeque、Zig std.fifo。

| API | 说明 |
|-----|------|
| `queue_i32_new()` | 新建空队列 |
| `queue_i32_with_capacity(q, cap)` | 预分配；失败 -1 |
| `queue_i32_push_back(q, x)` / `queue_i32_push_front(q, x)` | 队尾/队首插入 |
| `queue_i32_pop_back(q)` / `queue_i32_pop_front(q)` | 队尾/队首弹出（空返回 0） |
| `queue_i32_get(q, i)` | 取第 i 个元素 |
| `queue_i32_len(q)` / `queue_i32_is_empty(q)` | 个数 / 是否为空 |
| `queue_i32_clear(q)` / `queue_i32_reserve(q, new_cap)` / `queue_i32_deinit(q)` | 清空 / 扩容 / 释放 |
