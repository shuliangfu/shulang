# std.sync — 互斥锁与同步原语

**模块路径**：`std/sync/`（mod.su + sync.c）  
**依赖**：core（extern C），无其它 .su 模块。与 std.thread 配合使用。  
**对标**：Rust std::sync::Mutex、Zig Thread.Mutex。

## API 概览

| 函数 | 说明 |
|------|------|
| `mutex_new(): *u8` | 创建新的互斥体；成功返回句柄（不透明指针），失败返回 0。 |
| `mutex_lock(m: *u8): i32` | 加锁，阻塞直到获取；返回 0 成功，-1 失败。 |
| `mutex_try_lock(m: *u8): i32` | 尝试加锁，不阻塞；返回 0 已获取，非 0 未获取。 |
| `mutex_unlock(m: *u8): i32` | 解锁；返回 0 成功，-1 失败。 |
| `mutex_free(m: *u8): void` | 销毁并释放互斥体；调用后 m 不可再使用。 |

## 与 Zig / Rust 对标

| 我们的 API | Zig 对应 | Rust 对应 |
|------------|----------|-----------|
| `mutex_new()` | `Thread.Mutex{}` | `Mutex::new(T)` |
| `mutex_lock(m)` | `m.lock()` | `m.lock().unwrap()` |
| `mutex_try_lock(m)` | 无标准 try_lock | `m.try_lock().ok()` |
| `mutex_unlock(m)` | `m.unlock()` | 由 guard drop 或 `MutexGuard` 释放 |
| `mutex_free(m)` | 由 allocator 管理 | `Drop` 或 `into_inner()` |

语义：同一线程内 lock 后必须 unlock；free 前必须先 unlock。RwLock、Once 见 P2 可选或 P3。

## 实现说明

- **POSIX**：`pthread_mutex_t`，堆分配后返回指针；链接时需 `-lpthread`。
- **Windows**：`CRITICAL_SECTION`，`InitializeCriticalSection` / `EnterCriticalSection` / `TryEnterCriticalSection` / `LeaveCriticalSection` / `DeleteCriticalSection`。
- 互斥体句柄类型为 `*u8`（不透明指针），仅用于传给本模块函数，不得解引用。
