# std.fs — 高性能文件 API（大文件、极致并发与吞吐、性能压榨到极致）

本模块提供与 POSIX 一致的 open/read/write/close，以及 mmap 只读/可写、pread/pwrite、O_DIRECT、fadvise、madvise、copy_file_range，面向**大文件**与**性能压榨到极致**。

## 已实现（当前能力）

| 能力 | 说明 |
|------|------|
| **大块顺序 I/O** | `fs_read` / `fs_write`，建议 count ≥ `fs_read_chunk()`（1MiB）减少 syscall。 |
| **大文件只读零拷贝** | `fs_mmap_ro(path, &size)` 整文件只读 mmap；Linux 有 madvise 顺序提示；Windows CreateFileMapping + FILE_MAP_READ。 |
| **可写零拷贝** | `fs_mmap_rw(path, &size)` 整文件可写 mmap；Linux MAP_SHARED；Windows PAGE_READWRITE + FILE_MAP_WRITE。 |
| **同一 fd 多线程并发** | `fs_pread` / `fs_pwrite` 带 offset，多线程并行读/写不同区间。 |
| **极致吞吐顺序读（三平台）** | `fs_open_read_direct(path)`：Linux O_DIRECT / macOS F_NOCACHE / Windows FILE_FLAG_NO_BUFFERING；buf 与 offset 须对齐 `fs_direct_align()`。 |
| **O_DIRECT 对齐** | `fs_direct_align()` 返回对齐要求（字节），避免硬编码。 |
| **内核访问提示（Linux）** | `fs_fadvise_sequential(fd)` 顺序访问提示；`fs_fadvise_willneed(fd, offset, len)` 预取提示，压榨预读与缓存。 |
| **零拷贝/复制文件** | Linux：`fs_copy_file_range` 内核零拷贝；macOS/Windows：ReadFile/WriteFile 循环回退。 |
| **分散读/集中写** | `fs_readv2`/`fs_writev2` 两段、`fs_readv4`/`fs_writev4` 四段；Linux/macOS readv/writev，Windows 多段 ReadFile/WriteFile。 |
| **零拷贝文件→socket** | Linux `fs_sendfile`；Windows `TransmitFile`（需链 ws2_32 + mswsock）。 |
| **范围刷盘（Linux）** | `fs_sync_range(fd, offset, len)` 将 [offset, offset+len) 写回磁盘；Windows 当前 no-op。 |
| **预分配（Linux/Windows）** | `fs_fallocate(fd, offset, len)`：Linux fallocate；Windows SetFilePointerEx + SetEndOfFile。 |
| **打开模式** | `fs_open_append(path)` 追加写（不存在则创建）；`fs_open_create(path)` 写打开且存在不截断。 |
| **错误码** | `fs_last_error()` 返回上次 fs_* 失败时的平台错误码（errno / GetLastError）。 |
| **大页提示（Linux）** | mmap 映射 ≥2MB 时自动 madvise(MADV_HUGEPAGE)，减少 TLB 未命中。 |
| **与 std.io 联合压榨** | 文件 fd 作为 std.io 的 handle，走 io_uring/kqueue/IOCP 批量提交。 |

## 与 std.io 联合极致压榨

**std.fs 已内置 import std.io**，用户侧**仅需 `import std.fs`** 即可使用下列 fd 接口，走 io_uring/readv 极致压榨（无需再写 `import std.io`）：

- **单次大块**：`read_fd(fd, ptr, len)` / `write_fd(fd, ptr, len)`，推荐 `len ≥ fs_read_chunk()`。
- **多段批量**：`read_batch_fd(fd, p0, l0, p1, l1, p2, l2, p3, l3, n)` / `write_batch_fd(fd, ...)`，一次 submit 最多 4 段。
- **handle 转换**：`handle_from_fd(fd)` 将 fd 转为 io handle，可与 std.io 其它 API 配合。

```text
import std.fs;

let fd: i32 = fs_open_read(path);
if fd >= 0 {
  fs_fadvise_sequential(fd);
  let n: i32 = read_fd(fd, buf, fs_read_chunk());
  let total: i32 = read_batch_fd(fd, b0, L, b1, L, b2, L, b3, L, 4);
  fs_close(fd);
}
```

## 可继续压榨的方向

- **异步 + 批量**：同一 fd 多段并发时，用 std.io 的 `read_batch_fd` / `write_batch_fd`（io_uring 多 SQE 一次 submit）；可开放 8 段 batch、submit 与 wait 分离实现真正异步。
- **Linux**：ring 扩大(512→2K/4K)、SQPOLL/fixed buffer 优化；已与手写 C + io_uring 同水平，属同一水平上的微调。
- **macOS**：无 io_uring，已用 kqueue+readv、F_NOCACHE（open_read_direct）；可补 Dispatch I/O。
- **Windows**：已补全 mmap（CreateFileMapping/MapViewOfFile）、无缓冲打开（FILE_FLAG_NO_BUFFERING）、readv2/writev2（两段 ReadFile/WriteFile）、copy_file_range（ReadFile/WriteFile 循环）、TransmitFile、fallocate（SetEndOfFile）；`fs_sync_range` 为 no-op。链接 TransmitFile 时需 ws2_32 + mswsock（MSVC 已 pragma，MinGW 需 `-lws2_32 -lmswsock`）。

**是否已压榨到极致？与三平台对比能否超越？与 Zig 能否比肩/超越？** 见 [PERF-ASSESSMENT.md](PERF-ASSESSMENT.md)：Linux 已与内核能力同水平；macOS 已合理；Windows 已补全；**§五** 与 Zig std.fs/std.io 对比，结论为可比肩、在「开箱即用高性能 IO」上可超越 Zig 标准库。

## std.fs 完善度小结

**当前已完善**：三平台（Linux / macOS / Windows）核心与可选补充均已实现。

- **基础 I/O**：fs_open_read/fs_open_write/fs_close、fs_open_append（追加写）、fs_open_create（存在不截断）、fs_read/fs_write、pread/pwrite、fs_read_chunk。
- **mmap**：fs_mmap_ro、fs_mmap_rw、fs_munmap（Linux 含 madvise；Windows CreateFileMapping/MapViewOfFile）。
- **高性能**：fs_open_read_direct + fs_direct_align（Linux O_DIRECT / macOS F_NOCACHE / Windows FILE_FLAG_NO_BUFFERING）、fs_readv2/fs_writev2、fs_readv4/fs_writev4、fs_copy_file_range（Linux 零拷贝；macOS/Windows 读+写回退）、fs_sendfile、fs_fallocate、fs_sync_range（Windows 为 no-op）、fadvise（仅 Linux）。
- **错误码**：fs_last_error() 返回上次失败时的平台错误码（errno / GetLastError），便于细粒度诊断。
- **与 std.io 联合**：read_fd、write_fd、read_batch_fd、write_batch_fd、handle_from_fd，用户仅 `import std.fs` 即可。

**可选补充已全部落地**：macOS copy_file_range 读+写回退、macOS open_read_direct（F_NOCACHE）、fs_open_append/fs_open_create、fs_last_error、fs_readv4/fs_writev4 均已实现。

## 使用示例

```text
// 大文件整文件读（零拷贝 + 顺序提示）
let size: usize = 0;
let p: *u8 = fs_mmap_ro(path, &size);
if p != 0 { ... 使用 p[0..size-1] ...; fs_munmap(p, size); }

// 可写 mmap 改完即落盘
let p2: *u8 = fs_mmap_rw(path, &size);
if p2 != 0 { ... 修改 p2[...] ...; fs_munmap(p2, size); }

// 顺序读前提示内核，压榨预读
let fd: i32 = fs_open_read(path);
if fd >= 0 { fs_fadvise_sequential(fd); 循环 fs_read(fd, buf, fs_read_chunk()); fs_close(fd); }

// 多线程同文件并发读不同区间
// 线程 i：fs_pread(fd, buf, chunk, i * chunk)

// 极致吞吐顺序读（Linux，buf 须对齐 fs_direct_align()）
let fd2: i32 = fs_open_read_direct(path);
if fd2 >= 0 { 循环 fs_read(fd2, aligned_buf, chunk); fs_close(fd2); }

// 零拷贝复制（Linux）：从 fd_in 当前偏移复制 len 到 fd_out 当前偏移
let n: i64 = fs_copy_file_range(fd_in, fd_out, len);

// 分散读/集中写：一次 syscall 两段
let r: i64 = fs_readv2(fd, buf0, len0, buf1, len1);
let w: i64 = fs_writev2(fd, buf0, len0, buf1, len1);

// 文件→socket 零拷贝（Linux）
let sent: i64 = fs_sendfile(socket_fd, file_fd, count);

// 大文件顺序写：预分配 + 写后范围刷盘，重叠压榨
fs_fallocate(fd, 0, total_len);
// ... 循环 fs_write(fd, buf, chunk) ...
fs_sync_range(fd, 0, chunk);

// 追加写 / 存在不截断
let fd_a: i32 = fs_open_append(path);
if fd_a >= 0 { fs_write(fd_a, buf, len); fs_close(fd_a); }
let fd_c: i32 = fs_open_create(path);
if fd_c >= 0 { fs_write(fd_c, buf, len); fs_close(fd_c); }

// 失败时取平台错误码
let fd2: i32 = fs_open_read(bad_path);
if fd2 < 0 { let err: i32 = fs_last_error(); /* errno / GetLastError */ }

// 四段分散读/集中写
let r4: i64 = fs_readv4(fd, b0, L0, b1, L1, b2, L2, b3, L3);
let w4: i64 = fs_writev4(fd, b0, L0, b1, L1, b2, L2, b3, L3);
```
