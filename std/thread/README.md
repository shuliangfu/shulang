# std.thread — 线程（spawn/join/self）

多核易用：与 std.net 多 worker 配合压榨性能；每线程一 io_uring，spawn N 个线程即可跑满 N 核。

## API

| 函数 | 说明 |
|------|------|
| `thread_self(): i64` | 当前线程 ID |
| `thread_create(entry: usize, arg: usize): i64` | 创建线程；entry 为 C 函数地址 `void* (*)(void*)`，arg 传入；成功返回 thread_id，失败返回 0 |
| `thread_create_with_stack(entry: usize, arg: usize, stack_size: usize): i64` | 创建线程并指定栈大小；stack_size 为 0 表示默认；多 worker 时可传 262144 等省内存 |
| `thread_join(thread_id: i64): i32` | 等待线程结束；返回 0 成功，-1 失败 |
| `thread_set_affinity_self(cpu_index: i32): i32` | 将当前线程绑定到指定 CPU（绑核）；Linux/Windows 已实现，macOS 内核不支持返回 -1 |
| `thread_set_affinity(thread_id: i64, cpu_index: i32): i32` | 将指定线程绑定到指定 CPU；Linux/Windows 已实现 |
| `thread_set_qos_class_self(qos_class: i32): i32` | **仅 macOS**：设置当前线程 QoS，提升调度优先级（无法绑核时的替代）；0=default，1=interactive，2=user_initiated（worker 建议），3=utility，4=background |
| `thread_dummy_entry_ptr(): usize` | 测试用 C 入口地址，可 `thread_create(thread_dummy_entry_ptr(), 0)` 验证 |

## 性能（压榨）

- **零成本抽象**：POSIX 上 thread_create/thread_join 直接映射 pthread，热路径无分配；Windows 上每次 spawn 有一次小块 malloc（传参需要），join 后无残留。
- **多核**：与 std.net 配合时每线程一 io_uring，spawn N 即跑满 N 核；线程池由上层（如 listen_workers）或用户实现。
- 详见：`analysis/std.thread性能压榨.md`。

## 约定

- **entry**：当前 .su 无函数指针，需传 C 函数地址（usize）；后续语言支持 `&fn` 后可直接传 .su 函数。
- 链接：`import std.thread` 时链入 std/thread/thread.o；Unix 需 `-lpthread`，Windows 用 CreateThread。

## 使用示例（测试用）

```su
import std.thread;
function main(): i32 {
  let tid: i64 = thread_create(thread_dummy_entry_ptr(), 0);
  if (tid == 0) { return 1; }
  if (thread_join(tid) != 0) { return 2; }
  return 0;
}
```
