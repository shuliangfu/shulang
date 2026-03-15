# std.log — 日志级别与 stderr

**路径**：`std/log/`（mod.su + log.c）  
**依赖**：core。**性能**：零分配，单次 write。

| API | 说明 |
|-----|------|
| `set_min_level(level): void` | 0=DEBUG, 1=INFO, 2=WARN, 3=ERROR |
| `log(level, ptr, len): i32` | 写 "[LEVEL] " + 消息 + 换行到 stderr |
| `level_debug/info/warn/error(): i32` | 返回级别常量 |
